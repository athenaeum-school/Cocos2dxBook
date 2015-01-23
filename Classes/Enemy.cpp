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
#include "Player.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;
//敵NPCの攻撃確率
const int SUCCESS_RATE = 2;

Enemy::Enemy() :
 m_isAttacked(true)
{
	setAtkPower(0);
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
	//HPバーを追加
	Hud::getInstance()->initHpBar(this);
	//レイドHPに追加
	OM::getInstance()->addRaidHp(this->getHP());
	//エネミーカウント増加
	OM::getInstance()->addEnemyCount();
	//vectorとmapコンテナに追加
	OM::getInstance()->addGameObject(this);
	
	return this;
}

void Enemy::onStateEnter()
{
	//死亡していたら抜ける
	this->isDeadWithRet();
	
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
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
	this->isDeadWithRet();

	attack();
	hitCheck();
}

void Enemy::onStateExit()
{
	this->isDeadWithRet();

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
	//毎ターン最低１体が、50%の確率で攻撃する確率
	if (randomAttack(SUCCESS_RATE) == 0)
	{
		setIsAttacked(false);
	}
	else if (OM::getInstance()->getEnemyCount() == 1)
	{
		//残り１体になると必ず攻撃
		setIsAttacked(false);
	}
}

void Enemy::resultExit()
{
	//リザルト状態が終了すると同時に、敵NPCの消去処理
	setHP(0);
	setIsDead(true);
	if (getHpBar() && this->getChildByTag(kTag_hpbarBg))
	{
		getHpBar()->removeFromParent();
		this->removeChildByTag(kTag_hpbarBg);
	}
	OM::getInstance()->setEnemyCount(0);
	this->runAction(CCFadeOut::create(0));
}

int Enemy::randomAttack(int value)
{
	//敵NPCの最大数 % (敵NPCの最大数 * value)を返す
	int enemyCount = OM::getInstance()->getEnemyCount();
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
	//死亡しているか攻撃済みならtrue
	if (m_isDead || m_isAttacked)
	{
		return true;
	}
	return false;
}