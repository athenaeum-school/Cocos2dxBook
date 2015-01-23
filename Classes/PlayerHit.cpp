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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

PlayerHit::PlayerHit(){}

PlayerHit::~PlayerHit(){}

void PlayerHit::hitCheck()
{
	//敗北していたら抜ける
	this->isDeadWithRet();

	CCPoint wispPosition = this->getPosition();
	EnemyAttack *enemyAttack = static_cast<EnemyAttack *>(MS::getInstance()->getChildByTag(kTag_enemyAttack));
	//攻撃の当たり判定
	if (enemyAttack)
	{
		//敵の攻撃がウィスプの描画領域に触れたらtrue
		bool isContact = enemyAtkRect(enemyAttack).containsPoint(wispPosition);
		if (isContact)
		{
			CCLOG("wispHit");
			damage(enemyAttack);
			enemyAttack->removeFromParentAndCleanup(true);
		}
	}

}

CCRect PlayerHit::enemyAtkRect(EnemyAttack *enemyAttack)
{
	//敵NPC攻撃描画判定
	CCRect atkRect = CCRectMake(enemyAttack->getPositionX() - (enemyAttack->getContentSize().width / 10),
		enemyAttack->getPositionY() - (enemyAttack->getContentSize().height / 10),
		enemyAttack->getContentSize().width / 2, enemyAttack->getContentSize().height / 2);

	return atkRect;
}

void PlayerHit::damage(EnemyAttack *atkPower)
{
	//ダメージ
	int damage = atkPower->getAtkPower();

	if (damage > m_hp)
	{
		//HPがマイナスに表示されるのを防ぐ
		m_hp -= m_hp;
	}
	else
	{
		m_hp -= damage;
	}
	//HPバーに反映
	Hud::getInstance()->drawHpBar(this);
	//HPラベルに反映
	Hud::getInstance()->drawHpLabel();
	Hud::getInstance()->damageLabel(this->getPosition(), atkPower->getAtkPower());
	CCLOG("wispdamageHp%d", m_hp);
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	Hud::getInstance()->getAnime()->swingAnime(this);
	if (m_hp <= 0)
	{
		setIsDead(true);
		died();
	}
}

void PlayerHit::died()
{
	if (m_isDead)
	{
		setHP(0);
		Hud::getInstance()->getAnime()->wispDyingAnime(this);
	}
}

//ウィスプと壁の衝突判定
//西
void PlayerHit::collisionBlockWest()
{
	if (isLessThanRadius(m_nextPosition.x))
	{
		m_nextPosition.x = this->radius();
		//バウンド時の摩擦
		m_acceleration.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}
//東
void PlayerHit::collisionBlockEast()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(m_nextPosition.x, screenSize.width))
	{
		m_nextPosition.x = screenSize.width - this->radius();
		m_acceleration.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}
//北
void PlayerHit::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(m_nextPosition.y, screenSize.height)) {
		m_nextPosition.y = screenSize.height - this->radius();
		m_acceleration.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}

}
//南
void PlayerHit::collisionBlockSouth()
{
	if (isLessThanRadius(m_nextPosition.y))
	{
		m_nextPosition.y = this->radius();
		m_acceleration.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す（南、西）
bool PlayerHit::isLessThanRadius(float wispNextPos)
{
	if (wispNextPos < this->radius())
	{
		return true;
	}
	return false;
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す（北、東）
bool PlayerHit::isGreaterThanRadius(float wispNextPos, float screenwh)
{
	if (wispNextPos > screenwh - this->radius())
	{
		return true;
	}
	return false;
}
