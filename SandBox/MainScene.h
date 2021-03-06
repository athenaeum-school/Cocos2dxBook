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

enum tag
{
	kTag_background = 1,
	kTag_arrow,
	kTag_wisp,
	kTag_enemy,
	kTag_enemyAttack,
	kTag_ready,
	kTag_fire,
	kTag_retry,
	ktag_touch,
	kTag_hpbarBg,
};

enum zOrder
{
	z_background = 1,
	z_arrow,
	z_enemy,
	z_wisp,
	z_enemyAttack,
	z_explode,
	z_vanish,
	z_star,
	z_retry,
	z_touch,
	z_hpBarBg,
	z_hpbar,
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

	CC_SYNTHESIZE(cocos2d::CCTouch *, m_pBeganTouch, BeganTouch);
	CC_SYNTHESIZE(cocos2d::CCTouch *, m_pMovedTouch, MovedTouch);
	CC_SYNTHESIZE(cocos2d::CCTouch *, m_pEndedTouch, EndedTouch);

	static cocos2d::CCScene* createScene();
	CREATE_FUNC(MainScene);
    virtual bool init();  
	void update(float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

private:

	static MainScene *s_pInstance;
	
	MainScene();
	~MainScene();

};

typedef MainScene MS;

#endif /*defined(__WillYard__MainScene__)*/
