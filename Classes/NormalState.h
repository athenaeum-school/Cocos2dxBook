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

    virtual void stateUpdate(float dt);
    virtual bool onStateEnter();
    virtual bool onStateExit();
    virtual bool onTouchBeganEvent();
	virtual void onTouchMovedEvent();
	virtual void onTouchEndedEvent();
    
    virtual std::string getStateID() { return s_normalID; }
	
    NormalState();
    ~NormalState();

	CC_SYNTHESIZE(cocos2d::CCPoint, _wispVector, WispVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, _wispNextPosition, WispNextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _enemyVector, EnemyVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, _enemyNextPosition, EnemyNextPosition);

private:
   
	Player *_wisp;
	
   static const std::string s_normalID;
    
    void switchState();
    void normalToEnemy();
    void normalToResult();
	void calcCollision();
	void onCollisionFast(float distOne, float distTwo, float radius, Enemy *enemy);
	float calcVector(Enemy *enemy);
	float CalcDiff(float nextPos, float getPos);
	float CalcSum(float powOne, float powTwo);
	bool isLessThanRadius(float dist, float radius);
	bool isGreaterThanCount(int count);
	
};


#endif /* defined(__WillYard__NormalState__) */
