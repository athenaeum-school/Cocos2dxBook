/*
* EnemyHit.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyHit.h"
#include "MainScene.h"

EnemyHit::EnemyHit():
_isContacted(false)
{}

EnemyHit::~EnemyHit(){}

void EnemyHit::hitCheck()
{
	if (!isNormalState())
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

CCRect EnemyHit::setEnemyRect()
{
	//敵NPCのダメージ判定描画領域
	CCRect enemyRect = CCRectMake(this->getPositionX() - (this->getContentSize().width / 4.0),
		this->getPositionY() - (this->getContentSize().height / 4.0),
		this->getContentSize().width / 2.0, this->getContentSize().height / 2.0);
	return enemyRect;
}

bool EnemyHit::isDeadWithAttacking()
{
	//敵NPCが生存していて、ウィスプが攻撃中ならばtrue
	if (!_isDead && _wisp->getIsAttacking())
	{
		return true;
	}
	return false;
}

bool EnemyHit::isContanctWithContacted(bool isContact)
{
	if (isContact && !_isContacted)
	{
		return true;
	}
	return false;
}

void EnemyHit::damage()
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
	_hud->drawHpbar(this);
	CCLOG("EnemyHP : %d", _hp);

	if (_hp <= 0)
	{
		setIsDead(true);
		died();
	}
}

void EnemyHit::normalDamage(int playerAtk)
{
	//通常ダメージ
	_hp -= playerAtk;
	_om->damageRaidHp(playerAtk);
}

void EnemyHit::overDamage()
{
	//レイドHPとのずれを無くすため、オーバーダメージを防ぐ処理
	int margeDamage = _hp;
	_hp -= margeDamage;
	_om->damageRaidHp(margeDamage);
}

void EnemyHit::died()
{
	if (_isDead)
	{
		setHP(0);
		//敵NPCの数を減らす
		_om->drawEnemyCount();
		_hud->getAnime()->enemyDyingAnime(this);
	}
}
