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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

const std::string NormalState::s_normalID = "NORMAL";
//ショットパワー倍率
const float SHOT_POWER = 0.5;

NormalState::NormalState() {
    std::cout << "NormalState::NormalState() normal state constructor\n";
	_main = Main::getInstance();
	_om = Om::getInstance();
	_cm = Cm::getInstance();
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
	_enemy = Enemy::create("enemy3.png", SHOT_POWER, SHOT_POWER);
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


	//ウィスプの状態を更新
	setWispNextPosition(_wisp->getNextPosition());
	//ウィスプの推進力
	setWispVector(_wisp->getVector());
	setWispVector(ccpMult(_wispVector, 0.98f));
	//当たり判定
	//敵NPCの設定
	setEnemyNextPosition(_enemy->getNextPosition());
	setEnemyVector(_enemy->getVector());

	float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
	float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());

	float distOne = _cm->Calc(pow(diffx, 2), pow(diffy, 2));
	float distTwo = _cm->Calc(pow(_wisp->getPositionX() - _enemyNextPosition.x, 2), pow(_wisp->getPositionY() - _enemyNextPosition.y, 2));

	//衝突
	onCollision(distOne, distTwo, calcVector());

	//最後に、ウィスプの推進力と次の目標地点に設定
	_wisp->setVector(_wispVector);
	_wisp->setNextPosition(_wispNextPosition);

	//次の目標地点へ移動
	//_enemy->setPosition(_enemy->getNextPosition());
	_wisp->setPosition(_wisp->getNextPosition());
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

//衝突と減速処理
void NormalState::onCollision(float distOne, float distTwo, float radius){

	//衝突判定2（バウンド時）
	if (_cm->isLessThanDist(distOne, radius) || _cm->isLessThanDist(distTwo, radius)) {
		CCLOG("secondHit");

		//ウィスプとエネミーの距離を取得
		float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
		float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());
		//ウィスプと敵NPCの衝突時の運動量を計算
		float mag_wisp = _cm->Calc(pow(_wispVector.x, 2), pow(_wispVector.y, 2));
		float mag_enemy = _cm->Calc(pow(_enemyVector.x, 2), pow(_enemyVector.y, 2));

		//衝突時の摩擦調整
		//float force = sqrt(mag_wisp + mag_enemy) * 0.5;
		float force = sqrt(mag_wisp + mag_enemy) * 0.8f;
		float angle = atan2(diffy, diffx);

		_wispVector.x = force * cos(angle);
		_wispVector.y = (force * sin(angle));

		_wispNextPosition.x = _enemyNextPosition.x + (_enemy->radius() + _wisp->radius() + force) * cos(angle);
		_wispNextPosition.y = _enemyNextPosition.y + (_enemy->radius() + _wisp->radius() + force) * sin(angle);

		_cm->damageToEnemy();
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system48.mp3");
	}

}

	float NormalState::calcVector(){
		/*if ((float)(_wisp->getPositionX() - _wispNextPosition.x <= 1)){
		if ((float)(_wisp->getPositionY() - _wispNextPosition.y <= 1)){
		if (_wispVector.x > 5, _wispVector.y > 5){
		float squared_radius = pow(_enemy->radius() + _wisp->radius(), 2);
		return squared_radius;
		}
		}
		}else*/
		if (_wispVector.x < 10, _wispVector.y < 10){
			return 0;
		}

		float squared_radius = pow(_enemy->radius() + _wisp->radius(), 2);
		return squared_radius;
	}
