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
	CCRect wispRect = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp))->boundingBox();

	bool isContact_interSects = setEnemyRect().intersectsRect(wispRect);
	//�GNPC�̕`��̈�ɐG��Ă��āA����܂łɐG��Ă��Ȃ��A���A�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
	if (isContanctWithContacted(isContact_interSects) && isAliveWithAttacking())
	{
		//�_���[�W����
		damage();
		//HudLayer�̃C���X�^���X���Ăяo��
		//�_���[�W���̃A�j���[�V����
		Hud::getInstance()->getAction()->enemyDamageAction(this);
		//AudioComponent�Ō��ʉ����Đ�����t���O
		this->setIsPlayHitSE(true);
		//��x�G�ꂽ��A�����܂ŐG��Ȃ��Ȃ�i�d�������蔻���h���t���O�j
		setIsContacted(true);
	}
	else if (!isContact_interSects)
	{
		//���ꂽ��A�܂����肪�����悤��
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
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ�ΐ^
	if (!this->m_isDead && wisp->getIsAttacking())
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
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	int playerAtkPower = wisp->getAtkPower();
	
	//�_���[�W��\��
	Hud::getInstance()->damageLabel(this->getPosition(), wisp->getAtkPower());
	//�q�b�g����\�����A�X�V����
	Hud::getInstance()->addHitCountLabel();

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
		this->setIsDead(true);
		died();
	}
}

void EnemyHit::normalDamage(int playerAtkPower)
{
	//�ʏ�_���[�W
	this->m_hp -= playerAtkPower;
	//ObjectManager�̃C���X�^���X���Ăяo���A���LHP�����炷
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
		//HP�o�[��������
		this->removeHpBar();
		//AudioComponent�Ō��ʉ����Đ�����t���O
		this->setIsPlayDyingSE(true);
		//AudioComponent�̍폜
		delete this->m_pAudio;
		m_pAudio = NULL;
	}
}
