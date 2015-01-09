/*
* NormalState.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "NormalState.h"
#include "MainScene.h"

using namespace cocos2d;

const std::string NormalState::s_normalID = "NORMAL";

NormalState::NormalState() {
    std::cout << "NormalState::NormalState() normal state constructor\n";
	_main = Main::getInstance();
	_om = Om::getInstance();
}

NormalState::~NormalState() {
	//CC_SAFE_RELEASE(_enemy);
}

	//初期化
bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
	//ウィスプ生成
	_wisp = Player::create();
	//エネミー生成
	//Enemy::create(ccp(436, 125), "enemy2.png")->addEnemy();
	//背景生成
	_om->initBackground();
	
	//コンテナにゲームオブジェクトを代入
	_gObjects = _om->getGameObjects();
	
	return true;
}

void NormalState::stateUpdate(float dt) {
	//_gObjectsに追加されたゲームオブジェクトから関数を呼び出す
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it){
		// Game::Instance()->getStateMachine()->changeState(new AlarmState());
		(*it)->stateUpdate(dt);
		/*GameObject * enemys = _gm->findGameObject("enemy");
		if (enemys){
			enemys->update(dt);
		}*/
	}
	_wisp->stateUpdate(dt);
}

bool NormalState::onTouchBeganEvent(){
	return _wisp->wispTouchBegan();
}

void NormalState::onTouchMovedEvent(){
	_wisp->wispTouchMoved();
}

void NormalState::onTouchEndedEvent(){
	_wisp->wispTouchEnded();
}


	//状態遷移時の処理
bool NormalState::onStateExit() {
    return true;
}

