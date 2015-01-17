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


//状態のID
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
	//ターン開始ラベル表示
	turnOnEnemy();
	//コンテナにゲームオブジェクトを代入
	setGameObjects();
	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//ゲームオブジェクトのonStateEnter()を実行
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
	//ゲームオブジェクトのStateUpdate()を実行
	objectStateUpdate(dt);
	//次の状態へ
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
	//ターン開始ラベル表示
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *turn = CCSprite::create("enemtState_turn.png");
	turn->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	turn->setOpacity(0);
	_hud->addChild(turn);
	//ラベルフェードアウト後、setIsTurn()を実行
	CCSequence *fadeTurn = CCSequence::create(CCFadeIn::create(0.5), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(EnemyState::setIsTurn)), CCRemoveSelf::create(), NULL);
	turn->runAction(fadeTurn);
}

void EnemyState::setIsTurn()
{
	//フラグをtrueにし、stateUpdate()を開始
	_isTurn = true;
}

void EnemyState::switchState()
{
	if (_wisp->getIsDead() && isGreaterThanCount(90))
	{
		//ウィスプが消滅し、タイマーが190を超えたらResultStateへ
		if (isGreaterThanCount(190))
		{
			enemyToResult();
		}
	}
	else if (isGreaterThanCount(100))
	{
		//タイマーが100を超えたらプレイヤーのターンへ
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