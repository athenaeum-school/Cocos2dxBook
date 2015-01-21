/*
* GameObject.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__GameObject__
#define __WillYard__GameObject__

#include <iostream>
#include <cocos2d.h>

class MainScene;
class HudLayer;
class ObjectManager;

class GameObject : public cocos2d::CCSprite
{
public:

	CC_SYNTHESIZE(int, _hp, HP);
	CC_SYNTHESIZE(int, _maxHp, MaxHP);
	CC_SYNTHESIZE(int, _atk, Atk);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(std::string, _stateID, StateID);
	CC_SYNTHESIZE(cocos2d::CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _vector, Vector);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCProgressTimer *, _hpBar, HpBar);

	virtual void onStateEnter() = 0;
	virtual void onStateExit() = 0;
	virtual void stateUpdate(float dt) = 0;
	
	void setPosition(const cocos2d::CCPoint& pos);
	float radius();

	float getHpRatio();

protected:

	MainScene *_main;
	HudLayer *_hud;
	ObjectManager *_om;

	void setStateID();
	bool isNormalState();
	bool isEnemyState();
	bool isResultState();
	void isDeadWithRet();

	GameObject();
	~GameObject();

};


#endif /* defined(__WillYard__GameObject__) */
