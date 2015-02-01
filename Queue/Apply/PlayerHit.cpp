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
	//�s�k���Ă����甲����
	if (this->getIsDead())
	{
		return;
	}

	CCPoint wispPosition = this->getPosition();
	EnemyAttack *enemyAttack = static_cast<EnemyAttack *>(MS::getInstance()->getChildByTag(kTag_enemyAttack));
	//�U���̓����蔻��
	if (enemyAttack)
	{
		//�G�̍U�����E�B�X�v�̕`��̈�ɐG�ꂽ��^��
		bool isContact = enemyAtkRect(enemyAttack).containsPoint(wispPosition);
		if (isContact)
		{
			CCLOG("wispHit");
			//AudioQueue�Ō��ʉ����Đ�����t���O��^��
			this->setIsPlayHitSE(true);
			//�_���[�W
			damage(enemyAttack);
			//���������U�����폜
			enemyAttack->removeFromParent();
		}
	}

}

CCRect PlayerHit::enemyAtkRect(EnemyAttack *enemyAttack)
{
	//�GNPC�U���`��̈�
	CCRect atkRect = CCRectMake(enemyAttack->getPositionX() - (enemyAttack->getContentSize().width / 10),
		enemyAttack->getPositionY() - (enemyAttack->getContentSize().height / 10),
		enemyAttack->getContentSize().width / 2, enemyAttack->getContentSize().height / 2);

	return atkRect;
}

void PlayerHit::damage(EnemyAttack *atkPower)
{
	//�_���[�W
	int damage = atkPower->getAtkPower();

	if (damage > this->m_hp)
	{
		//HP���}�C�i�X�ɕ\�������̂�h��
		this->m_hp -= this->m_hp;
	}
	else
	{
		this->m_hp -= damage;
	}
	//HudLayer�̃C���X�^���X���Ăяo���AHP�o�[�ɔ��f
	Hud::getInstance()->drawHpBar(this);
	//HP���x���ɔ��f
	Hud::getInstance()->drawHpLabel();
	Hud::getInstance()->damageLabel(this->getPosition(), atkPower->getAtkPower());
	//�h���A�N�V����
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
		//�s�k���̃A�N�V����
		Hud::getInstance()->getAction()->dyingAction(this);
		//AudioQueue�Ō��ʉ����Đ�����t���O
		this->setIsPlayDyingSE(true);
	}
}

//�E�B�X�v�ƕǂ̏Փ˔���
//��
void PlayerHit::collisionBlockWest()
{
	if (isLessThanRadius(this->m_nextPosition.x))
	{
		this->m_nextPosition.x = this->getRadius();
		//�o�E���h���̖��C
		this->m_acceleration.x *= -0.8f;
		//AudioQueue�Ō��ʉ����Đ�����t���O
		this->setIsPlayHitBlockSE(true);
	}
}
//��
void PlayerHit::collisionBlockEast()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(this->m_nextPosition.x, screenSize.width))
	{
		this->m_nextPosition.x = screenSize.width - this->getRadius();
		this->m_acceleration.x *= -0.8f;
		//AudioQueue�Ō��ʉ����Đ�����t���O
		this->setIsPlayHitBlockSE(true);
	}
}
//�k
void PlayerHit::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(this->m_nextPosition.y, screenSize.height)) {
		this->m_nextPosition.y = screenSize.height - this->getRadius();
		this->m_acceleration.y *= -0.8f;
		//AudioQueue�Ō��ʉ����Đ�����t���O
		this->setIsPlayHitBlockSE(true);
	}

}
//��
void PlayerHit::collisionBlockSouth()
{
	if (isLessThanRadius(this->m_nextPosition.y))
	{
		this->m_nextPosition.y = this->getRadius();
		this->m_acceleration.y *= -0.8f;
		//AudioQueue�Ō��ʉ����Đ�����t���O
		this->setIsPlayHitBlockSE(true);
	}
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ��i��A���j
bool PlayerHit::isLessThanRadius(float wispNextPos)
{
	if (wispNextPos < this->getRadius())
	{
		return true;
	}
	return false;
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ��i�k�A���j
bool PlayerHit::isGreaterThanRadius(float wispNextPos, float screenwh)
{
	if (wispNextPos > screenwh - this->getRadius())
	{
		return true;
	}
	return false;
}
