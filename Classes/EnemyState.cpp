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
#include "SimpleAudioEngine.h"
#include "ResultState.h"


using namespace CocosDenshion;
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
{
}

EnemyState::~EnemyState()
{	
}

bool EnemyState::onStateEnter()
{
	CCLOG("Changed : enemyState");
	//�^�[���J�n���x���\��
	turnOnEnemy();

	//�R���e�i�ɃQ�[���I�u�W�F�N�g����
	_gObjects = _om->getGameObjects();

	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));

	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->onStateEnter();
	}

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
	
	//kTag_enemy�^�O�������Q�[���I�u�W�F�N�g���R���e�i����擾���AUpdate����
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->stateUpdate(dt);
	}

	
	if (_wisp->getIsDead() && ++_timer > 90)
	{
		//�E�B�X�v�����ł��A_timer��190�𒴂�����ResultState��
		if (++_timer > 190)
		{
			enemyToResult();
		}
	}
	else if (++_timer > 100)
	{
		_timer = 0;
		enemyToNormal();
	}
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