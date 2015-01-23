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

class Player : public PlayerHit
{
public:
	
	CC_SYNTHESIZE(bool, m_canFire, CanFire);
	CC_SYNTHESIZE(bool, m_isAttacking, IsAttacking);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_force, Force);
	CC_SYNTHESIZE(int, m_timer, Timer);
	
	static Player* create();

	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	void addPower(int power);
	void drawPower(int power);
	void startTimer();
	void resetWisp();

private:

	float m_angle;

	Player* initWisp();
	void addForceToWisp();
	bool isNext();
	void createArrow(cocos2d::CCPoint movePoint);
	void arrowSettings(cocos2d::CCSprite *arrow, cocos2d::CCPoint movePoint);
	float calcOffset(float angle);
	cocos2d::CCPoint calcForce(cocos2d::CCPoint endPoint);
	
	Player();
	~Player();

};

#endif /*defined(__WillYard__Player__)*/
