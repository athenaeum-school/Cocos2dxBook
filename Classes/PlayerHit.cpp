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
	//�s�k���Ă����甲����
	if (_isDead)
	{
		return;
	}

	CCPoint wispPosition = this->getPosition();
	EnemyAttack *enemyAttack = static_cast<EnemyAttack *>(_main->getChildByTag(kTag_enemyAttack));
	//�U���̓����蔻��
	if (enemyAttack)
	{
		//�G�̍U�����E�B�X�v�̕`��̈�ɐG�ꂽ��true
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
	//�GNPC�U���`�攻��
	CCRect atkRect = CCRectMake(enemyAttack->getPositionX() - (enemyAttack->getContentSize().width / 10),
		enemyAttack->getPositionY() - (enemyAttack->getContentSize().height / 10),
		enemyAttack->getContentSize().width / 2, enemyAttack->getContentSize().height / 2);

	return atkRect;
}

void PlayerHit::damage(EnemyAttack *atk)
{
	//�_���[�W
	int damage = atk->getAtk();

	if (damage > _hp)
	{
		//HP���}�C�i�X�ɕ\�������̂�h��
		_hp -= _hp;
	}
	else
	{
		_hp -= damage;
	}
	//HP���x���ɔ��f
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

//�E�B�X�v�ƕǂ̏Փ˔���
//��
void PlayerHit::collisionBlockWest()
{
	if (gThanRadius(_nextPosition.x))
	{
		_nextPosition.x = this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}
//��
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
//�k
void PlayerHit::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.y, screenSize.height)) {
		_nextPosition.y = screenSize.height - this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}

}
//��
void PlayerHit::collisionBlockSouth()
{
	if (gThanRadius(_nextPosition.y))
	{
		_nextPosition.y = this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ�
bool PlayerHit::gThanRadius(float wispNextPos)
{
	if (wispNextPos < this->radius())
	{
		return true;
	}
	return false;
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ�
bool PlayerHit::lessThanRadius(float wispNextPos, float screenwh)
{
	if (wispNextPos > screenwh - this->radius())
	{
		return true;
	}
	return false;
}
