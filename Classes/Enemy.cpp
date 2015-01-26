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
	this->setAtkPower(0);
	this->setHP(0);
	this->setMaxHP(0);
}

Enemy::~Enemy(){}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//敵NPCのステータスを追加
	//引数のstatusInit()は純粋仮想関数であり、派生クラス（敵NPCタイプ）に応じて、実装を変えている
	this->initWithFile(statusInit(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - this->getRadius() * 1.0));
	//フェードインのため、透明に
	this->setOpacity(0);
	//移動しながらフェードインするアクション
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - this->getRadius() * 10.0)), NULL);
	this->runAction(fadeIn);
	//待機アクション（純粋仮想関数）
	setIdleAction();
	//HPバーを追加
	Hud::getInstance()->initHpBar(this);
	//ObjectManagerのシングルトンを呼び出す
	//レイドHPに追加
	OM::getInstance()->addRaidHp(this->getHP());
	//エネミーカウント増加
	OM::getInstance()->addEnemyCount();
	//vectorコンテナに追加
	OM::getInstance()->addGameObject(this);
	
	return this;
}

void Enemy::onStateEnter()
{
	//死亡していたら以降の処理をしない
	this->isDeadWithRet();
	
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//状態のIDをメンバーへ代入
	this->setStateID();
	//状態の判別
	if (this->isNormalState())
	{
		this->setIsContacted(false);
	}
	else if (this->isEnemyState())
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
	else if (this->isResultState())
	{
		
	}
}

void Enemy::onStateExit()
{
	this->isDeadWithRet();

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
		if (this->getHpBar() && this->getChildByTag(kTag_hpbarBg))
		{
			//m_hpBarはHudLayerにaddChildしているため、子自身で消去処理
			this->getHpBar()->removeFromParent();
			//hpBar_bgはこのクラスにaddChildしているため、this->で消去
			this->removeChildByTag(kTag_hpbarBg);
		}
		//敵NPCの総数をリセット
		OM::getInstance()->setEnemyCount(0);
		//敵NPCを見えなくさせるアクション
		this->runAction(CCFadeOut::create(0));
	}
}

void Enemy::stateUpdate(float dt)
{
	this->isDeadWithRet();

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
	//死亡しているか、攻撃済みまたは敵NPCターン以外なら攻撃をしない
	if (isDeadOrAttacked() || !this->isEnemyState())
	{
		return;
	}
		//設定敵NPC種別に応じて、攻撃を生成
		EnemyAttack::create(this);
		//攻撃済みのフラグを立てる
		setIsAttacked(true);
}

bool Enemy::isDeadOrAttacked()
{
	//死亡しているか攻撃済みならtrue
	if (this->m_isDead || m_isAttacked)
	{
		return true;
	}
	return false;
}