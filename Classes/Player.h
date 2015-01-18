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

class MainScene;

class Player : public GameObject {
private:

	Player* initWisp();
	bool gThanRadius(float wispNextPos);
	bool lessThanRadius(float wispNextPos, float screenwh);
	void addForceToWisp();
	cocos2d::CCRect enemyAtkRect(EnemyAttack *enemyAttack);
	cocos2d::CCPoint calcForce(cocos2d::CCPoint endPoint);

public:
	
	CC_SYNTHESIZE(bool, _canFire, CanFire);
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);
	CC_SYNTHESIZE(bool, _isContacted, IsContacted);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(cocos2d::CCPoint, _touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, _force, Force);
	CC_SYNTHESIZE(int, _timer, Timer);
	
	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	void damage(EnemyAttack *atk);
	void hitCheck();
	void addPower(int power);
	void drawPower(int power);
	
	static Player* create();
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();

	void startTimer();
	void resetWisp();

	Player();
	~Player();
};

#endif /*defined(__WillYard__Player__)*/
