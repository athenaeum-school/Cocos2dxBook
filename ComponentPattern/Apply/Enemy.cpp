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
#include "Player.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;
//�GNPC�̍U���m��
const int SUCCESS_RATE = 2;

Enemy::Enemy():
m_isAttacked(true)
{}

Enemy::~Enemy(){}

void Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//�GNPC�̃X�e�[�^�X��ǉ�
	//������statusInit()�͏������z�֐��ł���A�h���N���X�i�GNPC�^�C�v�j�ɉ����āA������ς���
	this->initWithFile(initStatus(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - this->getRadius() * 1.0));
	//�t�F�[�h�C���̂��߁A������
	this->setOpacity(0);
	//�ړ����Ȃ���t�F�[�h�C������A�N�V����
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - this->getRadius() * 10.0)), NULL);
	this->runAction(fadeIn);
	//�ҋ@�A�N�V�����i�������z�֐��j
	setIdleAction();
	//HP�o�[��ǉ�
	Hud::getInstance()->initHpBar(this);
	//ObjectManager�̃C���X�^���X���Ăяo���A���LHP�ɒǉ�
	OM::getInstance()->addRaidHp(this->getHP());
	//�G�l�~�[�J�E���g����
	OM::getInstance()->addEnemyCount();
	//vector�R���e�i�ɒǉ�
	OM::getInstance()->addGameObject(this);
}

void Enemy::onStateEnter()
{
	//���S���Ă�����ȍ~�̏������s�Ȃ�Ȃ�
	if (this->m_isDead)
	{
		return;
	}
	
	//��Ԃ�ID�������o�[�֑��
	this->setStateID();
	//��Ԃ̔���
	if (this->isNormalState())
	{
		this->setIsContacted(false);
	}
	else if (this->isEnemyState())
	{
		//���^�[���G�����̂����Œ�P�̂��A50%�̊m���ōU������m��
		if (randomAttack(SUCCESS_RATE) == 0)
		{
			setIsAttacked(false);
		}
		else if (OM::getInstance()->getEnemyCount() == 1)
		{
			//�c��P�̂ɂȂ�ƕK���U��
			setIsAttacked(false);
		}
	}
	else if (this->isResultState())
	{
	
	}
}

void Enemy::onStateExit()
{
	if (this->m_isDead)
	{
		return;
	}

	if (this->isEnemyState())
	{
		//�܂��E�B�X�v�ɐG��Ă��Ȃ���Ԃɂ���
		this->setIsContacted(false);
	}
	else if (this->isResultState())
	{
		//���U���g��Ԃ��I������Ɠ����ɁA�GNPC�̏�������
		this->setHP(0);
		this->setIsDead(true);
		//�e�N���X����HP�o�[�����������Ăяo��
		this->removeHpBar();
		//�GNPC�̑��������Z�b�g
		OM::getInstance()->setEnemyCount(0);
		//�GNPC�������Ȃ�������A�N�V����
		this->runAction(CCFadeOut::create(0));
		//AudioComponent�̍폜
		delete this->m_pAudio;
		m_pAudio = NULL;
	}
}

void Enemy::stateUpdate(float dt)
{
	//���U���g��ԂȂ�A�ȍ~�̏������s�Ȃ�Ȃ�
	if (isResultState())
	{
		return;
	}
	//AudioComponent������ʉ����Ăяo��
	this->m_pAudio->update(dt, this);

	if (this->m_isDead)
	{
		return;
	}
	
	attack();
	this->hitCheck();
	
}



int Enemy::randomAttack(int value)
{
	//�GNPC�̑��� % (�GNPC�̑��� * value)��Ԃ�
	int enemyCount = OM::getInstance()->getEnemyCount();
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
	//�U���ς݂܂��͓GNPC�^�[���ȊO�Ȃ�U�������Ȃ�
	if (m_isAttacked || !this->isEnemyState())
	{
		return;
	}
		//�ݒ�GNPC��ʂɉ����āA�U���𐶐�
		EnemyAttack::create(this);
		//�U���ς݂̃t���O�𗧂Ă�
		setIsAttacked(true);
		//AudioComponent�Ō��ʉ����Đ�����t���O
		this->setIsAttackingEnemySE(true);
}