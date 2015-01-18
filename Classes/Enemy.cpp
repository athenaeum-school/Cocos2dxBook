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


USING_NS_CC;


Enemy::Enemy() :
 _isAttacked(true)
{
	setAtk(0);
	setHP(0);
	setMaxHP(0);
}


Enemy::~Enemy(){}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//敵NPCのステータスを追加
	this->initWithFile(statusInit(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 1 * this->radius()));
	//フェードインのため、透明に
	this->setOpacity(0);
	//移動しながらフェードインするアクション
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - 10 * this->radius())), NULL);
	this->runAction(fadeIn);
	//待機アクション
	setIdleAction();
	//レイドHPに追加
	_om->initRaidHp(this->getHP());
	//エネミーカウント増加
	_om->addEnemyCount();
	_om->addGameObjectMap(_addMapName, this);
	_om->addGameObject(this);
	
	return this;
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
	//50%の確率で攻撃が成功
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

void Enemy::resultExit()
{
	//リザルト状態が終了すると同時に、敵NPCの消去処理
	CCLOG("enemyOnStateExit:result");
	setHP(0);
	setIsDead(true);
	Om::getInstance()->setEnemyCount(0);
	this->runAction(CCFadeOut::create(0));
}

int Enemy::randomAttack(int value)
{
	//敵NPCの最大数 * valueまでの乱数を返す
	int enemyCount = _om->getEnemyCount();
	int random = enemyCount % calcRandom(1, enemyCount * value);
	return random;
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