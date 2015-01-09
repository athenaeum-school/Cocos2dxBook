/*
* CollisionManager.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__CollisionManager__
#define __WillYard__CollisionManager__

#include "cocos2d.h"
#include "ObjectSprite.h"

class CollisionManager : public cocos2d::CCLayer
{
public:

	static CollisionManager* getInstance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CollisionManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	CollisionManager();
	~CollisionManager();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(CollisionManager);
	CC_SYNTHESIZE_RETAIN(ObjectSprite *, _player, Player);
	CC_SYNTHESIZE_RETAIN(ObjectSprite *, _wisp, Wisp);
	CC_SYNTHESIZE(cocos2d::CCPoint, _touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCSize, _screenSize, ScreenSize);
	
	float CalcDiff(float nextPos, float getPos);
	float Calc(float powOne, float powTwo);
	bool isLessThanDist(float dist, float radius);
	
private:

	MainScene *_main;
	static CollisionManager *s_pInstance;
	
};

typedef CollisionManager Cm;

#endif /*defined(__WillYard__CollisionManager__)*/
