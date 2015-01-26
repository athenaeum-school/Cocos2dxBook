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

Enemy::Enemy() :
 m_isAttacked(true)
{
	this->setAtkPower(0);
	this->setHP(0);
	this->setMaxHP(0);
}

Enemy::~Enemy(){}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//�GNPC�̃X�e�[�^�X��ǉ�
	//������statusInit()�͏������z�֐��ł���A�h���N���X�i�GNPC�^�C�v�j�ɉ����āA������ς��Ă���
	this->initWithFile(statusInit(type).c_str());
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
	//ObjectManager�̃V���O���g�����Ăяo��
	//���C�hHP�ɒǉ�
	OM::getInstance()->addRaidHp(this->getHP());
	//�G�l�~�[�J�E���g����
	OM::getInstance()->addEnemyCount();
	//vector�R���e�i�ɒǉ�
	OM::getInstance()->addGameObject(this);
	
	return this;
}

void Enemy::onStateEnter()
{
	//���S���Ă�����ȍ~�̏��������Ȃ�
	this->isDeadWithRet();
	
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//��Ԃ�ID�������o�[�֑��
	this->setStateID();
	//��Ԃ̔���
	if (this->isNormalState())
	{
		this->setIsContacted(false);
	}
	else if (this->isEnemyState())
	{
		//���^�[���Œ�P�̂��A50%�̊m���ōU������m��
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
	this->isDeadWithRet();

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
		if (this->getHpBar() && this->getChildByTag(kTag_hpbarBg))
		{
			//m_hpBar��HudLayer��addChild���Ă��邽�߁A�q���g�ŏ�������
			this->getHpBar()->removeFromParent();
			//hpBar_bg�͂��̃N���X��addChild���Ă��邽�߁Athis->�ŏ���
			this->removeChildByTag(kTag_hpbarBg);
		}
		//�GNPC�̑��������Z�b�g
		OM::getInstance()->setEnemyCount(0);
		//�GNPC�������Ȃ�������A�N�V����
		this->runAction(CCFadeOut::create(0));
	}
}

void Enemy::stateUpdate(float dt)
{
	this->isDeadWithRet();

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
	//���S���Ă��邩�A�U���ς݂܂��͓GNPC�^�[���ȊO�Ȃ�U�������Ȃ�
	if (isDeadOrAttacked() || !this->isEnemyState())
	{
		return;
	}
		//�ݒ�GNPC��ʂɉ����āA�U���𐶐�
		EnemyAttack::create(this);
		//�U���ς݂̃t���O�𗧂Ă�
		setIsAttacked(true);
}

bool Enemy::isDeadOrAttacked()
{
	//���S���Ă��邩�U���ς݂Ȃ�true
	if (this->m_isDead || m_isAttacked)
	{
		return true;
	}
	return false;
}