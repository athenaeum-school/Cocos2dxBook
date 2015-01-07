/*
* MainScene.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__MainScene__
#define __WillYard__MainScene__

#include "cocos2d.h"
#include "ObjectSprite.h"
#include "CollisionManager.h"

class MainScene : public cocos2d::CCLayer
{
protected:

	MainScene();
	~MainScene();

private:

	static MainScene *s_pInstance;
	bool gThanRadius(float ballNextPos);
	bool lessThanRadius(float ballNextPos, float screenwh);

public:

	enum zOrder
	{
		z_enemy = 0,
		z_wisp,
	};

	static MainScene* getInstance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new MainScene();
			return s_pInstance;
		}

		assert(s_pInstance != NULL);
		return s_pInstance;
	}

    virtual bool init();  
	void update(float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	static cocos2d::CCScene* createScene();
    CREATE_FUNC(MainScene);
	CC_SYNTHESIZE_RETAIN(ObjectSprite *, _enemy, Enemy);
	CC_SYNTHESIZE_RETAIN(ObjectSprite *, _wisp, Wisp);
	CC_SYNTHESIZE_RETAIN(CollisionManager *, _cm, Cm);
	CC_SYNTHESIZE(bool, _canFire, CanFire);
	CC_SYNTHESIZE(cocos2d::CCPoint, _touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCSize, _screenSize, ScreenSize);
	CC_SYNTHESIZE(cocos2d::CCPoint, _wispVector, WispVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, _wispNextPosition, WispNextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _enemyVector, EnemyVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, _enemyNextPosition, EnemyNextPosition);

	
	
	cocos2d::CCPoint calcPos(cocos2d::CCPoint touch);
	bool gThanPos(int dist);
	cocos2d::CCPoint calcRetPos(cocos2d::CCPoint touch, int dist);
	void setChainOne(cocos2d::CCNode* chain1, cocos2d::CCPoint pos);
	cocos2d::CCNode* initChainOne(cocos2d::CCNode* chain1);
	cocos2d::CCPoint extendPos(cocos2d::CCNode* wisp);
	float extendAngle(cocos2d::CCNode* wisp);
	void removeAndAdd(cocos2d::CCNode* wisp, cocos2d::CCTouch* touch);
	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();
	void addForceToWisp();
	void onCollision(float distOne, float distTwo, float radius);
	cocos2d::CCNode * getWispTag();
	cocos2d::CCNode * getEnemyTag();
	void cSetwispNextPositionX(float f);
	void cSetwispNextPositionY(float f);
	float cGetWispVectorX();
	float cGetWispVectorY();
	float calcVector();
};

typedef MainScene Main;

#endif /*defined(__WillYard__MainScene__)*/
