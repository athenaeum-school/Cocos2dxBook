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
    float _tileWidth;
    float _tileHeight;
    float _mapWidth;
    float _mapHeight;
	Player* _wisp;
	Enemy* _enemy;
	std::vector<Enemy *> enemys;
	static const std::string s_normalID;
    
	void onCollision(float distOne, float distTwo, float radius);
	float calcVector();
};


#endif /* defined(__WillYard__NormalState__) */
