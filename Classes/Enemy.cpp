/*
* Enemy.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "Enemy.h"
#include "EnemyAttack.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ObjectManager.h"


USING_NS_CC;
using namespace CocosDenshion;


Enemy::Enemy() :
 _isAttacked(true),
 _isContacted(false),
 _isDead(false)
{
	setAtk(0);
	setHP(0);
	setMaxHP(0);
}


Enemy::~Enemy(){}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile(statusInit(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 1 * this->radius()));
	//�t�F�[�h�C���̂��߁A������
	this->setOpacity(0);
	//�ړ����Ȃ���t�F�[�h�C������A�N�V����
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - 10 * this->radius())), NULL);
	this->runAction(fadeIn);
	//�ҋ@�A�N�V����
	setIdleAction();
	//���C�hHP�ɒǉ�
	_om->initRaidHp(this->getHP());
	//�G�l�~�[�J�E���g����
	_om->addEnemyCount();
	_om->addGameObjectMap(_addMapName, this);
	_om->addGameObject(this);
	
	return this;
}


void Enemy::onStateEnter()
{
	if (_isDead)
	{
		return;
	}

	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//��Ԃ�ID�������o�[�֑��
	setStateID();
	//��Ԃ̔���
	if (isNormalState())
	{
		setIsContacted(false);
	}
	else if (isEnemyState())
	{
		onEnemyStateEnter();
	}
	else if (isResultState())
	{
		
	}
}

void Enemy::stateUpdate(float dt)
{
	if (_isDead)
	{
		return;
	}

	attack();
	hitCheck();
}

void Enemy::onStateExit()
{
	if (_isDead)
	{
		return;
	}

	if (isEnemyState())
	{
		setIsContacted(false);
	}
	else if (isResultState())
	{
		resultExit();
	}
}

void Enemy::onEnemyStateEnter()
{
	//50%�̊m���ōU��������
	if (randomAttack(2.0) < 1)
	{
		setIsAttacked(false);
	}
	else if (_om->getEnemyCount() == 1)
	{
		//�c��P�̂ɂȂ�ƁA75%�̊m���ōU��
		if (randomAttack(1.3) < 1)
		{
			setIsAttacked(false);
		}
	}
}

void Enemy::resultExit()
{
	//���U���g��Ԃ��I������Ɠ����ɁA�GNPC�̏�������
	CCLOG("enemyOnStateExit:result");
	setHP(0);
	setIsDead(true);
	Om::getInstance()->setEnemyCount(0);
	this->runAction(CCFadeOut::create(0));
}

int Enemy::randomAttack(int value)
{
	//�GNPC�̍ő吔 * value�܂ł̗�����Ԃ�
	int enemyCount = _om->getEnemyCount();
	int random = enemyCount % calcRandom(1, enemyCount * value);
	return random;
}

int Enemy::calcRandom(int min, int max)
{
	//min����max�̊Ԃ̐����������_���ɕԂ�
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}


void Enemy::attack()
{
	//���S���Ă��邩�A�U���ς݂܂��͓GNPC�^�[���ȊO�Ȃ�U�������Ȃ�
	if (isDeadOrAttacked() || !isEnemyState())
	{
		return;
	}
		//�ݒ�GNPC�^�C�v�ɉ����āA�U���𐶐�
		EnemyAttack::create(this);
		setIsAttacked(true);
}

bool Enemy::isDeadOrAttacked()
{
	if (_isDead || _isAttacked)
	{
		return true;
	}
	return false;
}

void Enemy::hitCheck()
{
	if (isEnemyState())
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


bool Enemy::isDeadWithAttacking()
{
	//�GNPC���������Ă��āA�E�B�X�v���U�����Ȃ��true
	if (!_isDead && _wisp->getIsAttacking())
	{
		return true;
	}
	return false;
}

bool Enemy::isContanctWithContacted(bool isContact)
{
	if (isContact && !_isContacted)
	{
		return true;
	}
	return false;
}

CCRect Enemy::setEnemyRect()
{
	//�GNPC�̃_���[�W����`��̈�
	CCRect enemyRect = CCRectMake(this->getPositionX() - (this->getContentSize().width / 4),
									this->getPositionY() - (this->getContentSize().height / 4),
									this->getContentSize().width / 2, this->getContentSize().height / 2);
	return enemyRect;
}

void Enemy::damage()
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
	
	CCLOG("EnemyHP : %d", _hp);

	if (_hp <= 0)
	{
		setIsDead(true);
		died();
	}
}


void Enemy::normalDamage(int playerAtk)
{
	//�ʏ�_���[�W
	_hp -= playerAtk;
	_om->damageRaidHp(playerAtk);
}

void Enemy::overDamage()
{
	//���C�hHP�Ƃ̂���𖳂������߁A�I�[�o�[�_���[�W��h������
	int margeDamage = _hp;
	_hp -= margeDamage;
	_om->damageRaidHp(margeDamage);
}

void Enemy::died()
{
	if (_isDead)
	{
		setHP(0);
		//�GNPC�̐������炷
		_om->drawEnemyCount();
		_hud->getAnime()->enemyDyingAnime(this);
	}
}
