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
		//�G�̍U�����E�B�X�v�̕`��̈�ɐG�ꂽ��true
		bool isContact = enemyAtkRect(enemyAttack).containsPoint(wispPosition);
		if (isContact)
		{
			CCLOG("wispHit");
			this->setIsPlayHitSE(true);
			damage(enemyAttack);
			enemyAttack->removeFromParentAndCleanup(true);
		}
		else if (!isContact)
		{
			this->setIsPlayHitSE(false);
		}
	}

}

CCRect PlayerHit::enemyAtkRect(EnemyAttack *enemyAttack)
{
	//�GNPC�U���`�攻��
	CCRect atkRect = CCRectMake(enemyAttack->getPositionX() - (enemyAttack->getContentSize().width / 10),
		enemyAttack->getPositionY() - (enemyAttack->getContentSize().height / 10),
		enemyAttack->getContentSize().width / 2, enemyAttack->getContentSize().height / 2);

	return atkRect;
}

void PlayerHit::damage(EnemyAttack *atkPower)
{
	//�_���[�W
	int damage = atkPower->getAtkPower();

	if (damage > m_hp)
	{
		//HP���}�C�i�X�ɕ\�������̂�h��
		m_hp -= m_hp;
	}
	else
	{
		m_hp -= damage;
	}
	//HP�o�[�ɔ��f
	Hud::getInstance()->drawHpBar(this);
	//HP���x���ɔ��f
	Hud::getInstance()->drawHpLabel();
	Hud::getInstance()->damageLabel(this->getPosition(), atkPower->getAtkPower());
	CCLOG("wispdamageHp%d", m_hp);
	Hud::getInstance()->getAction()->swingAction(this);
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
		Hud::getInstance()->getAction()->dyingAction(this);
		this->setIsPlayDyingSE(true);
		CCLOG("diued");
	}
}

//�E�B�X�v�ƕǂ̏Փ˔���
//��
void PlayerHit::collisionBlockWest()
{
	if (isLessThanRadius(m_nextPosition.x))
	{
		m_nextPosition.x = this->getRadius();
		//�o�E���h���̖��C
		m_acceleration.x *= -0.8f;
		//AudioComponent�Ō��ʉ���炷���߂̃t���O��^��
		this->setIsPlayHitBlockSE(true);
	}
}
//��
void PlayerHit::collisionBlockEast()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(m_nextPosition.x, screenSize.width))
	{
		m_nextPosition.x = screenSize.width - this->getRadius();
		m_acceleration.x *= -0.8f;
		this->setIsPlayHitBlockSE(true);
	}
}
//�k
void PlayerHit::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (isGreaterThanRadius(m_nextPosition.y, screenSize.height)) {
		m_nextPosition.y = screenSize.height - this->getRadius();
		m_acceleration.y *= -0.8f;
		this->setIsPlayHitBlockSE(true);
	}

}
//��
void PlayerHit::collisionBlockSouth()
{
	if (isLessThanRadius(m_nextPosition.y))
	{
		m_nextPosition.y = this->getRadius();
		m_acceleration.y *= -0.8f;
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
