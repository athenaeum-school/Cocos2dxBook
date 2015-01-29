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
	if (isContanctWithContacted(isContact_interSects) && isAliveWithAttacking())
	{
		damage();
		//HudLayerのシングルトンを呼び出す
		//ダメージ時のアニメーション
		Hud::getInstance()->getAction()->enemyDamageAction(this);
		//ダメージ効果音を鳴らすためのフラグを真に
		this->setIsPlayHitSE(true);
		//一度触れたら、離れるまで触れなくなる（重複当たり判定を防ぐフラグ）
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

bool EnemyHit::isAliveWithAttacking()
{
	//敵NPCが生存していて、ウィスプが攻撃中ならば真
	if (!this->m_isDead && m_pWisp->getIsAttacking())
	{
		return true;
	}
	return false;
}

bool EnemyHit::isContanctWithContacted(bool isContact_interSects)
{
	//敵NPCに触れる、その接触までに触れていなければ真
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
	//ヒット数を表示し、更新する
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
	//HPバーに反映
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
	int mergeDamage = m_hp;
	this->m_hp -= mergeDamage;
	OM::getInstance()->damageRaidHp(mergeDamage);
}

void EnemyHit::died()
{
	if (this->m_isDead)
	{
		this->setHP(0);
		//敵NPCの数を減らす
		OM::getInstance()->drawEnemyCount();
		Hud::getInstance()->getAction()->dyingAction(this);
		//死亡効果音を鳴らすためのフラグを真に
		this->setIsPlayDyingSE(true);
	}
}
