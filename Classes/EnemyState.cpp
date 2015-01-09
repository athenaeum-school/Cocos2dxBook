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

using namespace CocosDenshion;

const std::string EnemyState::s_enemyID = "ENEMY";

void EnemyState::s_enemyToNormal() {
	CCLOG("NormalState : changed");
    Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

void EnemyState::s_enemyToIdle() {
    //Game::Instance()->getStateMachine()->changeState(new IdleState());
}

EnemyState::EnemyState()
	:_timer(0)
{
	_main = Main::getInstance();
	_om = Om::getInstance();
	_cm = Cm::getInstance();
}

EnemyState::~EnemyState() {
}

void EnemyState::stateUpdate(float dt) {
	
	
	//enemyタグがついたゲームオブジェクトをコンテナから取得し、Updateする
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it){
		if ((*it)->getTag() == kTag_enemy)
		(*it)->stateUpdate(dt);
	}

	if (++_timer > 100)
	s_enemyToNormal();
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
	//コンテナにゲームオブジェクトを代入
	_gObjects = _om->getGameObjects();

	return true;
}

bool EnemyState::onStateExit() {
    return true;
}
