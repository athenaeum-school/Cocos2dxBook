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
	setAtkPower(0);
	setHP(0);
	setMaxHP(0);
}

Enemy::~Enemy(){}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//�GNPC�̃X�e�[�^�X��ǉ�
	this->initWithFile(statusInit(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 1 * this->radius()));
	//�t�F�[�h�C���̂��߁A������
	this->setOpacity(0);
	//�ړ����Ȃ���t�F�[�h�C������A�N�V����
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - 10 * this->radius())), NULL);
	this->runAction(fadeIn);
	//�ҋ@�A�N�V����
	setIdleAction();
	//HP�o�[��ǉ�
	Hud::getInstance()->initHpBar(this);
	//���C�hHP�ɒǉ�
	OM::getInstance()->addRaidHp(this->getHP());
	//�G�l�~�[�J�E���g����
	OM::getInstance()->addEnemyCount();
	//vector��map�R���e�i�ɒǉ�
	OM::getInstance()->addGameObject(this);
	
	return this;
}

void Enemy::onStateEnter()
{
	//���S���Ă����甲����
	this->isDeadWithRet();
	
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
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
	this->isDeadWithRet();

	attack();
	hitCheck();
}

void Enemy::onStateExit()
{
	this->isDeadWithRet();

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

void Enemy::resultExit()
{
	//���U���g��Ԃ��I������Ɠ����ɁA�GNPC�̏�������
	setHP(0);
	setIsDead(true);
	if (getHpBar() && this->getChildByTag(kTag_hpbarBg))
	{
		getHpBar()->removeFromParent();
		this->removeChildByTag(kTag_hpbarBg);
	}
	OM::getInstance()->setEnemyCount(0);
	this->runAction(CCFadeOut::create(0));
}

int Enemy::randomAttack(int value)
{
	//�GNPC�̍ő吔 % (�GNPC�̍ő吔 * value)��Ԃ�
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
	//���S���Ă��邩�U���ς݂Ȃ�true
	if (m_isDead || m_isAttacked)
	{
		return true;
	}
	return false;
}