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


//��Ԃ�ID
const std::string EnemyState::s_enemyID = "ENEMY";


void EnemyState::enemyToNormal()
{
	CCLOG("enemyToNormal : change");
    Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

void EnemyState::enemyToResult()
{
	Om::getInstance()->getStateMachine()->changeState(new ResultState());
}

EnemyState::EnemyState()
	:_timer(0)
	, _isTurn(false)
{}

EnemyState::~EnemyState(){}

bool EnemyState::onStateEnter()
{
	CCLOG("Changed : enemyState");
	//�^�[���J�n���x���\��
	turnOnEnemy();
	//�R���e�i�ɃQ�[���I�u�W�F�N�g����
	setGameObjects();
	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//�Q�[���I�u�W�F�N�g��onStateEnter()�����s
	objectStateEnter();

	return true;
}

bool EnemyState::onStateExit() 
{
	return true;
}

void EnemyState::stateUpdate(float dt) 
{
	if (!_isTurn)
	{
		return;
	}
	//�Q�[���I�u�W�F�N�g��StateUpdate()�����s
	objectStateUpdate(dt);
	//���̏�Ԃ�
	switchState();
}

bool EnemyState::onTouchBeganEvent()
{
	return false;
}

void EnemyState::onTouchMovedEvent()
{
}

void EnemyState::onTouchEndedEvent()
{	
}

void EnemyState::turnOnEnemy()
{
	//�^�[���J�n���x���\��
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *turn = CCSprite::create("enemtState_turn.png");
	turn->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	turn->setOpacity(0);
	_hud->addChild(turn);
	//���x���t�F�[�h�A�E�g��AsetIsTurn()�����s
	CCSequence *fadeTurn = CCSequence::create(CCFadeIn::create(0.5), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(EnemyState::setIsTurn)), CCRemoveSelf::create(), NULL);
	turn->runAction(fadeTurn);
}

void EnemyState::setIsTurn()
{
	//�t���O��true�ɂ��AstateUpdate()���J�n
	_isTurn = true;
}

void EnemyState::switchState()
{
	if (_wisp->getIsDead() && isGreaterThanCount(90))
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
		_timer = 0;
		enemyToNormal();
	}
}

bool EnemyState::isGreaterThanCount(int count)
{
	if (++_timer > count)
	{
		return true;
	}
	return false;
}