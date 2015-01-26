/*
* EnemyState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyState.h"
#include "NormalState.h"
#include "ResultState.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;

//��Ԃ�ID
const std::string EnemyState::s_enemyID = "ENEMY";

void EnemyState::enemyToNormal()
{
	//ObjectManager�̃C���X�^���X���Ăяo���ANormalState�֑J��
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

void EnemyState::enemyToResult()
{
	OM::getInstance()->getStateMachine()->changeState(new ResultState());
}

EnemyState::EnemyState()
	:m_timer(0)
	, m_isTurn(false)
{}

EnemyState::~EnemyState(){}

bool EnemyState::onStateEnter()
{
	//�^�[���J�n���x���\��
	turnOnEnemyImage();
	//�R���e�i�ɃQ�[���I�u�W�F�N�g����
	this->setGameObjects();
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//�Q�[���I�u�W�F�N�g��onStateEnter()�����s
	this->objectStateEnter();

	return true;
}

bool EnemyState::onStateExit() 
{
	return true;
}

void EnemyState::stateUpdate(float dt) 
{
	//�^�łȂ���Έȍ~�̏������s�Ȃ�Ȃ�
	if (!m_isTurn)
	{
		return;
	}
	//�Q�[���I�u�W�F�N�g��StateUpdate()�����s
	this->objectStateUpdate(dt);
	//���̏�Ԃ�
	switchState();
}

bool EnemyState::onTouchBeganEvent()
{
	return false;
}

void EnemyState::onTouchMovedEvent(){}

void EnemyState::onTouchEndedEvent(){}

void EnemyState::turnOnEnemyImage()
{
	//�^�[���J�n���x���\��
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *turn = CCSprite::create("enemtState_turn.png");
	turn->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	//�t�F�[�h�C���̂��߁A������
	turn->setOpacity(0);
	//HudLayer�̃C���X�^���X���Ăяo���A�����ɒǉ�
	Hud::getInstance()->addChild(turn);
	//���x���t�F�[�h�A�E�g��AsetIsTurn()�����s
	CCSequence *fadeTurn = CCSequence::create(CCFadeIn::create(0.5), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(EnemyState::setIsTurn)), CCRemoveSelf::create(), NULL);
	turn->runAction(fadeTurn);
}

void EnemyState::setIsTurn()
{
	//�t���O��true�ɂ��AstateUpdate()���J�n
	m_isTurn = true;
}

void EnemyState::switchState()
{
	if (m_pWisp->getIsDead() && isGreaterThanCount(90))
	{
		//�E�B�X�v�����ł��A�^�C�}�[��190�𒴂�����ResultState��
		if (isGreaterThanCount(190))
		{
			enemyToResult();
		}
	}
	else if (isGreaterThanCount(100))
	{
		//�^�C�}�[��100�𒴂�����v���C���[�̃^�[����
		m_timer = 0;
		enemyToNormal();
	}
}

bool EnemyState::isGreaterThanCount(int count)
{
	//m_timer��count�𒴂�����^
	if (++m_timer > count)
	{
		return true;
	}
	return false;
}