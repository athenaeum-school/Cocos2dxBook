/*
* PlayerHit.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "PlayerHit.h"
#include "MainScene.h"
#include "HudLayer.h"

USING_NS_CC;

PlayerHit::PlayerHit(){}

PlayerHit::~PlayerHit(){}

void PlayerHit::hitCheck()
{
	//敗北していたら抜ける
	if (this->getIsDead())
	{
		return;
	}

	CCPoint wispPosition = this->getPosition();
	EnemyAttack *enemyAttack = static_cast<EnemyAttack *>(MS::getInstance()->getChildByTag(kTag_enemyAttack));
	//攻撃の当たり判定
	if (enemyAttack)
	{
		//敵の攻撃がウィスプの描画領域に触れたら真に
		bool isContact = enemyAtkRect(enemyAttack).containsPoint(wispPosition);
		if (isContact)
		{
			CCLOG("wispHit");
			//AudioQueueで効果音を再生するフラグを真に
			this->setIsPlayHitSE(true);
			//ダメージ
			damage(enemyAttack);
			//当たった攻撃を削除
			enemyAttack->removeFromParent();
		}
	}

}

CCRect PlayerHit::enemyAtkRect(EnemyAttack *enemyAttack)
{
	//敵NPC攻撃描画領域
	CCRect atkRect = CCRectMake(enemyAttack->getPositionX() - (enemyAttack->getContentSize().width / 10),
		enemyAttack->getPositionY() - (enemyAttack->getContentSize().height / 10),
		enemyAttack->getContentSize().width / 2, enemyAttack->getContentSize().height / 2);

	return atkRect;
}

void PlayerHit::damage(EnemyAttack *atkPower)
{
	//ダメージ
	int damage = atkPower->getAtkPower();

	if (damage > this->m_hp)
	{
		//HPがマイナスに表示されるのを防ぐ
		this->m_hp -= this->m_hp;
	}
	else
	{
		this->m_hp -= damage;
	}
	//HudLayerのインスタンスを呼び出し、HPバーに反映
	Hud::getInstance()->drawHpBar(this);
	//HPラベルに反映
	Hud::getInstance()->drawHpLabel();
	Hud::getInstance()->damageLabel(this->getPosition(), atkPower->getAtkPower());
	//揺れるアクション
	Hud::getInstance()->getAction()->swingAction(this);
	if (this->m_hp <= 0)
	{
		this->setIsDead(true);
		died();
	}
}

void PlayerHit::died()
{
	if (this->m_isDead)
	{
		this->setHP(0);
		//敗北時のアクション
		Hud::getInstance()->getAction()->dyingAction(this);
		//AudioQueueで効果音を再生するフラグ
		this->setIsPlayDyingSE(true);
	}
}

//ウィスプと壁の衝突判定
//西
void PlayerHit::collisionBlockWest()
{
	if (isLessThanRadius(this->m_nextPosition.x))
	{
		this->m_nextPosition.x = this->getRadius();
		//バウンド時の摩擦
		this->m_acceleration.x *= -0.8f;
		//AudioQueueで効果音を再生するフラグ
		this->setIsPlayHitBlockSE(true);
	}
}
//東
void PlayerHit::collisionBlockEast()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(this->m_nextPosition.x, screenSize.width))
	{
		this->m_nextPosition.x = screenSize.width - this->getRadius();
		this->m_acceleration.x *= -0.8f;
		//AudioQueueで効果音を再生するフラグ
		this->setIsPlayHitBlockSE(true);
	}
}
//北
void PlayerHit::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(this->m_nextPosition.y, screenSize.height)) {
		this->m_nextPosition.y = screenSize.height - this->getRadius();
		this->m_acceleration.y *= -0.8f;
		//AudioQueueで効果音を再生するフラグ
		this->setIsPlayHitBlockSE(true);
	}

}
//南
void PlayerHit::collisionBlockSouth()
{
	if (isLessThanRadius(this->m_nextPosition.y))
	{
		this->m_nextPosition.y = this->getRadius();
		this->m_acceleration.y *= -0.8f;
		//AudioQueueで効果音を再生するフラグ
		this->setIsPlayHitBlockSE(true);
	}
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す（南、西）
bool PlayerHit::isLessThanRadius(float wispNextPos)
{
	if (wispNextPos < this->getRadius())
	{
		return true;
	}
	return false;
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す（北、東）
bool PlayerHit::isGreaterThanRadius(float wispNextPos, float screenwh)
{
	if (wispNextPos > screenwh - this->getRadius())
	{
		return true;
	}
	return false;
}
