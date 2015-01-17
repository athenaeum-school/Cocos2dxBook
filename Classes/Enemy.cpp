/*
* Enemy.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "Enemy.h"
#include "EnemyAttack.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ObjectManager.h"

USING_NS_CC;
using namespace CocosDenshion;

Enemy::Enemy(MainScene *main) 
: GameObject(main)
, _isAttacked(true)
, _isContacted(false)
, _isDead(false)
{
	setAtk(0);
	setHP(0);
	setMaxHP(0);
}


Enemy::~Enemy(){}

Enemy* Enemy::create(enemyType type, float xPos, float yPos)
{
	//エネミー生成
	Enemy * enemy = new Enemy(Main::getInstance());
	if (enemy)
	{
		enemy->initEnemy(type, xPos, yPos);
		enemy->autorelease();
		Main::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile(fileNameInit(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 1 * this->radius()));
	this->setOpacity(0);

	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - 10 * this->radius())), NULL);
	this->runAction(fadeIn);
	animationInit(type);
	//レイドHPに追加
	_om->initRaidHp(this->getHP());
	//エネミーカウント増加
	_om->addEnemyCount();
	_om->addGameObjectMap("enemy", this);
	_om->addGameObject(this);
	
	return this;
}

std::string Enemy::fileNameInit(enemyType type)
{
	std::string fileName;
	//エネミータイプに応じて、ステータスを設定
	switch (type)
	{
	case enemyType::kTag_rat1:
		fileName = "enemy1.png";
		this->setEtype(type);
		this->setHP(30);
		this->setMaxHP(30);
		this->setAtk(5);
		break;
	case enemyType::kTag_rat2:
		fileName = "enemy2.png";
		this->setEtype(type);
		this->setHP(60);
		this->setMaxHP(60);
		this->setAtk(10);
		break;
	case enemyType::kTag_vampire:
		fileName = "enemy3.png";
		this->setEtype(type);
		this->setHP(100);
		this->setMaxHP(100);
		this->setAtk(20);
		break;
	default:
		break;
	}

	return fileName;
}

void Enemy::animationInit(enemyType type)
{
	
	switch (type)
	{ 
		{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		_hud->getAnime()->enemyIdleAnime(this);
		break;
		}

		{
	case enemyType::kTag_vampire:
		_hud->getAnime()->enemy_vamp_idleAnime(this);
		break;
		}

		{
	default:
		break;
		}
	}

}


void Enemy::onStateEnter()
{
	if (_isDead)
	{
		return;
	}

	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//状態のIDをメンバーへ代入
	setStateID();
	//状態の判別
	if (isNormalState())
	{
		setIsContacted(false);
	}
	else if (isEnemyState())
	{
		onEnemyStateEnter();
	}
	else if (isResultState())
	{
		
	}
}

void Enemy::stateUpdate(float dt)
{
	if (_isDead)
	{
		return;
	}

	attack();
	hitCheck();
}

void Enemy::onStateExit()
{
	if (_isDead)
	{
		return;
	}

	if (isEnemyState())
	{
		setIsContacted(false);
	}
	else if (isResultState())
	{
		resultExit();
	}
}

void Enemy::onEnemyStateEnter()
{
	//敵NPCの残存数に応じて、攻撃する確率が上昇する
	if (randomAttack(2.0) < 1)
	{
		setIsAttacked(false);
	}
	else if (_om->getEnemyCount() == 1)
	{
		//残り１体になると、75%の確率で攻撃
		if (randomAttack(1.3) < 1)
		{
			setIsAttacked(false);
		}
	}
}

int Enemy::randomAttack(int value)
{
	//敵NPCの残存数に応じて、攻撃する確立が上昇
	int enemyCount = _om->getEnemyCount();
	int random = enemyCount % calcRandom(1, enemyCount * value);
	return random;
}


void Enemy::resultExit()
{
	//リザルト状態が終了すると同時に、敵NPCの消去処理
	CCLOG("enemyOnStateExit:result");
	setHP(0);
	setIsDead(true);
	Om::getInstance()->setEnemyCount(0);
	this->runAction(CCFadeOut::create(0));
}

int Enemy::calcRandom(int min, int max)
{
	//minからmaxの間の整数をランダムに返す
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}


void Enemy::attack()
{
	//死亡しているか、攻撃済みまたは敵NPCターン以外なら攻撃をしない
	if (isDeadOrAttacked() || !isEnemyState())
	{
		return;
	}
		//設定敵NPCタイプに応じて、攻撃を生成
		EnemyAttack::create(this);
		setIsAttacked(true);
}

bool Enemy::isDeadOrAttacked()
{
	if (_isDead || _isAttacked)
	{
		return true;
	}
	return false;
}

void Enemy::hitCheck()
{
	if (isEnemyState())
	{
		return;
	}

	CCPoint enemyPosition = this->getPosition();
	CCRect wispRect = _wisp->boundingBox();
	
	bool isContact = setEnemyRect().intersectsRect(wispRect);
	//敵NPCの描画領域に触れていて、それまでに触れていない、かつ、敵NPCが生存していて、ウィスプが攻撃中ならばtrue
	if (isContanctWithContacted(isContact) && isDeadWithAttacking())
	{
		damage();
		_hud->getAnime()->enemyDamageAnime(this);
		setIsContacted(true);
	}
	else if (!isContact)
	{
		setIsContacted(false);
	}

}


bool Enemy::isDeadWithAttacking()
{
	//敵NPCが生存していて、ウィスプが攻撃中ならばtrue
	if (!_isDead && _wisp->getIsAttacking())
	{
		return true;
	}
	return false;
}

bool Enemy::isContanctWithContacted(bool isContact)
{
	if (isContact && !_isContacted)
	{
		return true;
	}
	return false;
}

CCRect Enemy::setEnemyRect()
{
	//敵NPCのダメージ判定描画領域
	CCRect enemyRect = CCRectMake(this->getPositionX() - (this->getContentSize().width / 4),
									this->getPositionY() - (this->getContentSize().height / 4),
									this->getContentSize().width / 2, this->getContentSize().height / 2);
	return enemyRect;
}

void Enemy::damage()
{
	
	int playerAtk = _wisp->getAtk();
	//ダメージを表示
	_hud->damageToString(this->getPosition(), _wisp->getAtk());
	//ヒット数を表示
	_hud->addComboCount();

	if (playerAtk <= this->_hp)
	{
		//通常ダメージ
		normalDamage(playerAtk);
	}
	else if (playerAtk > this->_hp)
	{
		//レイドHPとの不整合を無くすため、オーバーダメージを防ぐ処理
		overDamage();
	}
	
	CCLOG("EnemyHP : %d", _hp);

	if (_hp <= 0)
	{
		setIsDead(true);
		died();
	}
}


void Enemy::normalDamage(int playerAtk)
{
	//通常ダメージ
	_hp -= playerAtk;
	_om->damageRaidHp(playerAtk);
}

void Enemy::overDamage()
{
	//レイドHPとのずれを無くすため、オーバーダメージを防ぐ処理
	int margeDamage = _hp;
	_hp -= margeDamage;
	_om->damageRaidHp(margeDamage);
}

void Enemy::died()
{
	if (_isDead)
	{
		setHP(0);
		//敵NPCの数を減らす
		_om->drawEnemyCount();
		_hud->getAnime()->enemyDyingAnime(this);
	}
}
