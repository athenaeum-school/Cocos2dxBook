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
	//�GNPC�̕`��̈�ɐG��Ă��āA����܂łɐG��Ă��Ȃ��A���A�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
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
	//�GNPC�̃_���[�W����`��̈�
	CCRect enemyRect = CCRectMake(this->getPositionX() - (this->getContentSize().width / 4.0),
		this->getPositionY() - (this->getContentSize().height / 4.0),
		this->getContentSize().width / 2.0, this->getContentSize().height / 2.0);
	return enemyRect;
}

bool EnemyHit::isDeadWithAttacking()
{
	//�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
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
	
	//�_���[�W��\��
	_hud->damageToString(this->getPosition(), _wisp->getAtk());
	//�q�b�g����\��
	_hud->addComboCount();

	if (playerAtk <= this->_hp)
	{
		//�ʏ�_���[�W
		normalDamage(playerAtk);
	}
	else if (playerAtk > this->_hp)
	{
		//���C�hHP�Ƃ̕s�����𖳂������߁A�I�[�o�[�_���[�W��h������
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
	//�ʏ�_���[�W
	_hp -= playerAtk;
	_om->damageRaidHp(playerAtk);
}

void EnemyHit::overDamage()
{
	//���C�hHP�Ƃ̂���𖳂������߁A�I�[�o�[�_���[�W��h������
	int margeDamage = _hp;
	_hp -= margeDamage;
	_om->damageRaidHp(margeDamage);
}

void EnemyHit::died()
{
	if (_isDead)
	{
		setHP(0);
		//�GNPC�̐������炷
		_om->drawEnemyCount();
		_hud->getAnime()->enemyDyingAnime(this);
	}
}
