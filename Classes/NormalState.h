/*
* NormalState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__NormalState__
#define __WillYard__NormalState__

#include "GameState.h"
#include <cocos2d.h>
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"

class NormalState : public GameState
{
public:

	CC_SYNTHESIZE(cocos2d::CCPoint, _wispVector, WispVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, _wispNextPosition, WispNextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _enemyVector, EnemyVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, _enemyNextPosition, EnemyNextPosition);

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

    std::string getStateID() override { return s_normalID; }
	
    NormalState();
    ~NormalState();

private:
   
	Player *_wisp;
    static const std::string s_normalID;
    
	void normalToEnemy();
	void normalToResult();
    void switchState();
	bool isLessThanZero();
	bool isGreaterThanCount(int count);
	void calcCollision();
	void onCollisionFast(float distOne, float distTwo, float radius, Enemy *enemy);
	bool isLessThanRadius(float dist, float radius);
	float CalcDiff(float nextPos, float getPos);
	float CalcSum(float powOne, float powTwo);
	float calcVector(Enemy *enemy);
	
};


#endif /* defined(__WillYard__NormalState__) */
