/*
* Player.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__Player__
#define __WillYard__Player__

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyAttack.h"
#include "PlayerHit.h"

class MainScene;

class Player : public PlayerHit {
private:

	Player* initWisp();
	void addForceToWisp();
	cocos2d::CCPoint calcForce(cocos2d::CCPoint endPoint);

public:
	
	CC_SYNTHESIZE(bool, _canFire, CanFire);
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);
	CC_SYNTHESIZE(bool, _isContacted, IsContacted);
	CC_SYNTHESIZE(cocos2d::CCPoint, _touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, _force, Force);
	CC_SYNTHESIZE(int, _timer, Timer);
	
	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	void addPower(int power);
	void drawPower(int power);
	
	static Player* create();
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	void startTimer();
	void resetWisp();

	Player();
	~Player();
};

#endif /*defined(__WillYard__Player__)*/
