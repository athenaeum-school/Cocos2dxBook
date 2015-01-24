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
#include "Player.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;

EnemyHit::EnemyHit():
m_isContacted(false)
{}

EnemyHit::~EnemyHit(){}

void EnemyHit::hitCheck()
{
	CCPoint enemyPosition = this->getPosition();
	CCRect wispRect = m_pWisp->boundingBox();

	bool isContact_interSects = setEnemyRect().intersectsRect(wispRect);
	//敵NPCの描画領域に触れていて、それまでに触れていない、かつ、敵NPCが生存していて、ウィスプが攻撃中ならばtrue
	if (isContanctWithContacted(isContact_interSects) && isDeadWithAttacking())
	{
		damage();
		Hud::getInstance()->getAnime()->enemyDamageAnime(this);
		//描画領域に触れていたら、触れなくなる（重複当たり判定を防ぐフラグ）
		setIsContacted(true);
	}
	else if (!isContact_interSects)
	{
		//離れたら、また判定がされるようにする
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
	if (!this->m_isDead && m_pWisp->getIsAttacking())
	{
		return true;
	}
	return false;
}

bool EnemyHit::isContanctWithContacted(bool isContact_interSects)
{
	if (isContact_interSects && !m_isContacted)
	{
		return true;
	}
	return false;
}

void EnemyHit::damage()
{

	int playerAtkPower = m_pWisp->getAtkPower();
	
	//ダメージを表示
	Hud::getInstance()->damageLabel(this->getPosition(), m_pWisp->getAtkPower());
	//ヒット数を表示
	Hud::getInstance()->addComboCountLabel();

	if (playerAtkPower <= this->m_hp)
	{
		//通常ダメージ
		normalDamage(playerAtkPower);
	}
	else if (playerAtkPower > this->m_hp)
	{
		//レイドHPとの不整合を無くすため、オーバーダメージを防ぐ処理
		overDamage();
	}
	Hud::getInstance()->drawHpBar(this);
	CCLOG("EnemyHP : %d", this->m_hp);

	if (this->m_hp <= 0)
	{
		setIsDead(true);
		died();
	}
}

void EnemyHit::normalDamage(int playerAtkPower)
{
	//通常ダメージ
	this->m_hp -= playerAtkPower;
	OM::getInstance()->damageRaidHp(playerAtkPower);
}

void EnemyHit::overDamage()
{
	//レイドHPとのずれを無くすため、オーバーダメージを防ぐ処理
	int margeDamage = m_hp;
	this->m_hp -= margeDamage;
	OM::getInstance()->damageRaidHp(margeDamage);
}

void EnemyHit::died()
{
	if (this->m_isDead)
	{
		this->setHP(0);
		//敵NPCの数を減らす
		OM::getInstance()->drawEnemyCount();
		Hud::getInstance()->getAnime()->enemyDyingAnime(this);
	}
}
