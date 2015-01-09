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

class MainScene;

class Player : public GameObject {
private:

	Player* initWisp();
	bool gThanRadius(float wispNextPos);
	bool lessThanRadius(float wispNextPos, float screenwh);
	void addForceToWisp();

public:
	
	CC_SYNTHESIZE(bool, _canFire, CanFire);
	CC_SYNTHESIZE(bool, _isContacted, IsContacted);
	CC_SYNTHESIZE(cocos2d::CCPoint, _touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, _force, Force);
	CC_SYNTHESIZE(int, _timer, Timer);


	virtual void stateUpdate(float dt);

	static Player* create();
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();

	void onCollisionPassing();
	void startTimer();

	Player(MainScene *main);
	~Player(void);
};

#endif /*defined(__WillYard__Player__)*/
