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
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "CollisionManager.h"


enum tag
{
	kTag_background = 1,
	kTag_wisp,
	kTag_enemy
};

enum zOrder
{
	z_background = 1,
	z_enemy,
	z_wisp,
	z_explode,
	z_star,
};

class MainScene : public cocos2d::CCLayer
{
protected:

	MainScene();
	~MainScene();

private:

	static MainScene *s_pInstance;
	ObjectManager *_om;
	CollisionManager *_cm;

public:

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

	static cocos2d::CCScene* createScene();
	CREATE_FUNC(MainScene);
    virtual bool init();  
	void update(float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	CC_SYNTHESIZE(cocos2d::CCTouch *, _beganTouch, BeganTouch);
	CC_SYNTHESIZE(cocos2d::CCTouch *, _movedTouch, MovedTouch);
	CC_SYNTHESIZE(cocos2d::CCTouch *, _endedTouch, EndedTouch);

};

typedef MainScene Main;

#endif /*defined(__WillYard__MainScene__)*/
