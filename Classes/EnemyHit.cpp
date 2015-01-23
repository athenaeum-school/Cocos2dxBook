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
	if (!isNormalState())
	{
		return;
	}

	CCPoint enemyPosition = this->getPosition();
	CCRect wispRect = m_pWisp->boundingBox();

	bool isContact_interSects = setEnemyRect().intersectsRect(wispRect);
	//�GNPC�̕`��̈�ɐG��Ă��āA����܂łɐG��Ă��Ȃ��A���A�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
	if (isContanctWithContacted(isContact_interSects) && isDeadWithAttacking())
	{
		damage();
		Hud::getInstance()->getAnime()->enemyDamageAnime(this);
		setIsContacted(true);
	}
	else if (!isContact_interSects)
	{
		setIsContacted(false);
	}

}

CCRect EnemyHit::setEnemyRect()
{
	//�GNPC�̃_���[�W����`��̈�
	CCRect enemyRect = CCRectMake(this->getPositionX() - (this->getContentSize().width / 4.0),
		this->getPositionY() - (this->getContentSize().height / 4.0),
		this->getContentSize().width / 2.0, this->getContentSize().height / 2.0);
	return enemyRect;
}

bool EnemyHit::isDeadWithAttacking()
{
	//�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
	if (!m_isDead && m_pWisp->getIsAttacking())
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

	int playerAtk = m_pWisp->getAtkPower();
	
	//�_���[�W��\��
	Hud::getInstance()->damageToString(this->getPosition(), m_pWisp->getAtkPower());
	//�q�b�g����\��
	Hud::getInstance()->addComboCount();

	if (playerAtk <= this->m_hp)
	{
		//�ʏ�_���[�W
		normalDamage(playerAtk);
	}
	else if (playerAtk > this->m_hp)
	{
		//���C�hHP�Ƃ̕s�����𖳂������߁A�I�[�o�[�_���[�W��h������
		overDamage();
	}
	Hud::getInstance()->drawHpbar(this);
	CCLOG("EnemyHP : %d", m_hp);

	if (m_hp <= 0)
	{
		setIsDead(true);
		died();
	}
}

void EnemyHit::normalDamage(int playerAtk)
{
	//�ʏ�_���[�W
	m_hp -= playerAtk;
	OM::getInstance()->damageRaidHp(playerAtk);
}

void EnemyHit::overDamage()
{
	//���C�hHP�Ƃ̂���𖳂������߁A�I�[�o�[�_���[�W��h������
	int margeDamage = m_hp;
	m_hp -= margeDamage;
	OM::getInstance()->damageRaidHp(margeDamage);
}

void EnemyHit::died()
{
	if (m_isDead)
	{
		setHP(0);
		//�GNPC�̐������炷
		OM::getInstance()->drawEnemyCount();
		Hud::getInstance()->getAnime()->enemyDyingAnime(this);
	}
}
