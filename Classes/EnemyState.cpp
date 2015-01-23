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

//状態のID
const std::string EnemyState::s_enemyID = "ENEMY";

void EnemyState::enemyToNormal()
{
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
	//ターン開始ラベル表示
	turnOnEnemy();
	//コンテナにゲームオブジェクトを代入
	setGameObjects();
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
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
	if (!m_isTurn)
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

void EnemyState::onTouchMovedEvent(){}

void EnemyState::onTouchEndedEvent(){}

void EnemyState::turnOnEnemy()
{
	//ターン開始ラベル表示
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *turn = CCSprite::create("enemtState_turn.png");
	turn->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	turn->setOpacity(0);
	Hud::getInstance()->addChild(turn);
	//ラベルフェードアウト後、setIsTurn()を実行
	CCSequence *fadeTurn = CCSequence::create(CCFadeIn::create(0.5), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(EnemyState::setIsTurn)), CCRemoveSelf::create(), NULL);
	turn->runAction(fadeTurn);
}

void EnemyState::setIsTurn()
{
	//フラグをtrueにし、stateUpdate()を開始
	m_isTurn = true;
}

void EnemyState::switchState()
{
	if (m_pWisp->getIsDead() && isGreaterThanCount(90))
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
		m_timer = 0;
		enemyToNormal();
	}
}

bool EnemyState::isGreaterThanCount(int count)
{
	if (++m_timer > count)
	{
		return true;
	}
	return false;
}