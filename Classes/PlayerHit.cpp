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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

PlayerHit::PlayerHit(){}

PlayerHit::~PlayerHit(){}

void PlayerHit::hitCheck()
{
	//敗北していたら抜ける
	if (_isDead)
	{
		return;
	}

	CCPoint wispPosition = this->getPosition();
	EnemyAttack *enemyAttack = static_cast<EnemyAttack *>(_main->getChildByTag(kTag_enemyAttack));
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

void PlayerHit::damage(EnemyAttack *atk)
{
	//ダメージ
	int damage = atk->getAtk();

	if (damage > _hp)
	{
		//HPがマイナスに表示されるのを防ぐ
		_hp -= _hp;
	}
	else
	{
		_hp -= damage;
	}
	//HPラベルに反映
	Hud::getInstance()->drawMyHpLabel();
	Hud::getInstance()->damageToString(this->getPosition(), atk->getAtk());
	CCLOG("wispdamageHp%d", _hp);
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	_hud->getAnime()->swingAnime(this);
	if (_hp <= 0)
	{
		CCLOG("wispDied");
		setHP(0);
		setIsDead(true);
		_hud->getAnime()->wispDyingAnime(this);
	}
}

//ウィスプと壁の衝突判定
//西
void PlayerHit::collisionBlockWest()
{
	if (gThanRadius(_nextPosition.x))
	{
		_nextPosition.x = this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}
//東
void PlayerHit::collisionBlockEast()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.x, screenSize.width))
	{
		_nextPosition.x = screenSize.width - this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}
//北
void PlayerHit::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.y, screenSize.height)) {
		_nextPosition.y = screenSize.height - this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}

}
//南
void PlayerHit::collisionBlockSouth()
{
	if (gThanRadius(_nextPosition.y))
	{
		_nextPosition.y = this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す
bool PlayerHit::gThanRadius(float wispNextPos)
{
	if (wispNextPos < this->radius())
	{
		return true;
	}
	return false;
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す
bool PlayerHit::lessThanRadius(float wispNextPos, float screenwh)
{
	if (wispNextPos > screenwh - this->radius())
	{
		return true;
	}
	return false;
}
