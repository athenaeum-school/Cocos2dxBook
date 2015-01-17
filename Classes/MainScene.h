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
#include "ObjectManager.h"
#include "HudLayer.h"


enum tag
{
	kTag_background = 1,
	kTag_wisp,
	kTag_enemy,
	kTag_enemyAttack,
	kTag_ready,
	kTag_fire,
	kTag_retry,
};

enum zOrder
{
	z_background = 1,
	z_enemy,
	z_wisp,
	z_enemyAttack,
	z_explode,
	z_vanish,
	z_star,
	z_retry,
};

class MainScene : public cocos2d::CCLayer
{
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

	CC_SYNTHESIZE(cocos2d::CCTouch *, _beganTouch, BeganTouch);
	CC_SYNTHESIZE(cocos2d::CCTouch *, _movedTouch, MovedTouch);
	CC_SYNTHESIZE(cocos2d::CCTouch *, _endedTouch, EndedTouch);

	static cocos2d::CCScene* createScene();
	CREATE_FUNC(MainScene);
    virtual bool init();  
	void update(float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

protected:

	MainScene();
	~MainScene();

private:

	static MainScene *s_pInstance;
	ObjectManager *_om;
	HudLayer *_hud;

};

typedef MainScene Main;

#endif /*defined(__WillYard__MainScene__)*/
