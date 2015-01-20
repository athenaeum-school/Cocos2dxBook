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
#include "PlayerHit.h"

class MainScene;

class Player : public PlayerHit {

public:
	
	CC_SYNTHESIZE(bool, _canFire, CanFire);
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);
	CC_SYNTHESIZE(cocos2d::CCPoint, _touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, _force, Force);
	CC_SYNTHESIZE(int, _timer, Timer);
	
	static Player* create();

	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	void addPower(int power);
	void drawPower(int power);
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	void startTimer();
	void resetWisp();

	Player();
	~Player();

private:

	Player* initWisp();
	void addForceToWisp();
	bool isNext();
	void createArrow(cocos2d::CCPoint movePoint);
	void arrowSettings(cocos2d::CCSprite *arrow, cocos2d::CCPoint movePoint);
	cocos2d::CCPoint calcForce(cocos2d::CCPoint endPoint);
	
};

#endif /*defined(__WillYard__Player__)*/
