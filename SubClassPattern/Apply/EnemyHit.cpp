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
	//�GNPC�̕`��̈�ɐG��Ă��āA����܂łɐG��Ă��Ȃ��A���A�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
	if (isContanctWithContacted(isContact_interSects) && isAliveWithAttacking())
	{
		damage();
		//HudLayer�̃V���O���g�����Ăяo��
		//�_���[�W���̃A�j���[�V����
		Hud::getInstance()->getAction()->enemyDamageAction(this);
		//�_���[�W���ʉ���炷���߂̃t���O��^��
		this->setIsPlayHitSE(true);
		//��x�G�ꂽ��A�����܂ŐG��Ȃ��Ȃ�i�d�������蔻���h���t���O�j
		setIsContacted(true);
	}
	else if (!isContact_interSects)
	{
		//���ꂽ��A�܂����肪�����悤�ɂ���
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

bool EnemyHit::isAliveWithAttacking()
{
	//�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ�ΐ^
	if (!this->m_isDead && m_pWisp->getIsAttacking())
	{
		return true;
	}
	return false;
}

bool EnemyHit::isContanctWithContacted(bool isContact_interSects)
{
	//�GNPC�ɐG���A���̐ڐG�܂łɐG��Ă��Ȃ���ΐ^
	if (isContact_interSects && !m_isContacted)
	{
		return true;
	}
	return false;
}

void EnemyHit::damage()
{

	int playerAtkPower = m_pWisp->getAtkPower();
	
	//�_���[�W��\��
	Hud::getInstance()->damageLabel(this->getPosition(), m_pWisp->getAtkPower());
	//�q�b�g����\�����A�X�V����
	Hud::getInstance()->addComboCountLabel();

	if (playerAtkPower <= this->m_hp)
	{
		//�ʏ�_���[�W
		normalDamage(playerAtkPower);
	}
	else if (playerAtkPower > this->m_hp)
	{
		//���C�hHP�Ƃ̕s�����𖳂������߁A�I�[�o�[�_���[�W��h������
		overDamage();
	}
	//HP�o�[�ɔ��f
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
	//�ʏ�_���[�W
	this->m_hp -= playerAtkPower;
	OM::getInstance()->damageRaidHp(playerAtkPower);
}

void EnemyHit::overDamage()
{
	//���C�hHP�Ƃ̂���𖳂������߁A�I�[�o�[�_���[�W��h������
	int mergeDamage = m_hp;
	this->m_hp -= mergeDamage;
	OM::getInstance()->damageRaidHp(mergeDamage);
}

void EnemyHit::died()
{
	if (this->m_isDead)
	{
		this->setHP(0);
		//�GNPC�̐������炷
		OM::getInstance()->drawEnemyCount();
		Hud::getInstance()->getAction()->dyingAction(this);
		//���S���ʉ���炷���߂̃t���O��^��
		this->setIsPlayDyingSE(true);
	}
}