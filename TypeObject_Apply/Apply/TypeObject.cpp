/*
* TypeObject.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "TypeObject.h"
#include "EnemyAttack.h"
#include "Player.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;
//敵NPCの攻撃確率
const int SUCCESS_RATE = 2;

Enemy::Enemy():
m_isAttacked(true)
{}

Enemy::~Enemy(){}

Enemy* Enemy::create(EnemyType *enemyType)
{
	//エネミー生成
	Enemy * enemy = new Enemy();
	if (enemy)
	{
		enemy->initEnemy(enemyType);
		enemy->autorelease();
		//MainSceneのインスタンスを呼び出し、そこに追加
		MS::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Enemy::initEnemy(EnemyType *enemyType)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//敵NPCのステータスを追加
	this->initWithFile(initStatus(enemyType).c_str());
	//配置座標を設定
	this->setPosition(ccp(screenSize.width * enemyType->getXPOS(), screenSize.height * enemyType->getYPOS() - this->getRadius() * 1.0));
	//フェードインのため、透明に
	this->setOpacity(0);
	//移動しながらフェードインするアクション
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * 0.6 - this->getRadius() * 10.0)), NULL);
	this->runAction(fadeIn);
	//待機アクション
	setIdleAction();
	//HPバーを追加
	Hud::getInstance()->initHpBar(this);
	//ObjectManagerのインスタンスを呼び出し、共有HPに追加
	OM::getInstance()->addRaidHp(this->getHP());
	//エネミーカウント増加
	OM::getInstance()->addEnemyCount();
}

std::string Enemy::initStatus(EnemyType *enemyType)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//EnemyConfigの設定に応じて、ステータスを設定
	std::string fileName = enemyType->getimageID();
	int hp = enemyType->getHp();
	int atkPower = enemyType->getAtkPower();
	enemyTypeTag typeTag = static_cast<enemyTypeTag>(enemyType->getEnemyTypeTag());
	this->setEnemyTypeTag(typeTag);
	this->setHP(hp);
	this->setMaxHP(hp);
	this->setAtkPower(atkPower);
	return fileName;
}

void Enemy::setIdleAction()
{
	//HudLayerのインスタンスを呼び出し、待機アクションを設定
	Hud::getInstance()->getAction()->enemyIdleAction(this, -0.2, 0.2);
}

void Enemy::onStateEnter()
{
	//死亡していたら以降の処理を行なわない
	if (this->m_isDead)
	{
		return;
	}
	
	//状態のIDをメンバーへ代入
	this->setStateID();
	//状態の判別
	if (this->isNormalState())
	{
		this->setIsContacted(false);
	}
	else if (this->isEnemyState())
	{
		//毎ターン敵総数のうち最低１体が、50%の確率で攻撃する確率
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
	else if (this->isResultState())
	{
		
	}
}

void Enemy::onStateExit()
{
	if (this->m_isDead)
	{
		return;
	}

	if (this->isEnemyState())
	{
		//まだウィスプに触れていない状態にする
		this->setIsContacted(false);
	}
	else if (this->isResultState())
	{
		//リザルト状態が終了すると同時に、敵NPCの消去処理
		this->setHP(0);
		this->setIsDead(true);
		//親クラスからHPバー消去処理を呼び出す
		this->removeHpBar();
		//敵NPCの総数をリセット
		OM::getInstance()->setEnemyCount(0);
		//敵NPCを見えなくさせるアクション
		this->runAction(CCFadeOut::create(0));
	}
}

void Enemy::stateUpdate(float dt)
{
	if (this->m_isDead)
	{
		return;
	}
	
	attack();
	this->hitCheck();
	
}



int Enemy::randomAttack(int value)
{
	//敵NPCの総数 % (敵NPCの総数 * value)を返す
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
	//攻撃済みまたは敵NPCターン以外なら攻撃をしない
	if (m_isAttacked || !this->isEnemyState())
	{
		return;
	}
		//設定敵NPC種別に応じて、攻撃を生成
		EnemyAttack::create(this);
		//攻撃済みのフラグを立てる
		setIsAttacked(true);
}