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
#include "ObjectManager.h"
#include "NormalState.h"
#include "CollisionManager.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

using namespace CocosDenshion;

const std::string EnemyState::s_enemyID = "ENEMY";

void EnemyState::s_enemyToNormal() {
    Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

void EnemyState::s_enemyToIdle() {
    //Game::Instance()->getStateMachine()->changeState(new IdleState());
}

EnemyState::EnemyState()
{
    
}

EnemyState::~EnemyState() {
    
}

void EnemyState::stateUpdate(float dt) {
	
}

bool EnemyState::onTouchBeganEvent(){
	return false;
}

void EnemyState::onTouchMovedEvent(){

}

void EnemyState::onTouchEndedEvent(){
	
}

void EnemyState::onInputEvent(CCPoint* pts) {
    
}

bool EnemyState::onStateEnter() {
	CCLOG("Changed : enemyState");
    return true;
}

bool EnemyState::onStateExit() {
    return true;
}
