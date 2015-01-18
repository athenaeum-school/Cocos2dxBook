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
   
	virtual void onStateEnter() = 0;
	virtual void onStateExit() = 0;
	virtual void stateUpdate(float dt) = 0;
	
	virtual void setPosition(const cocos2d::CCPoint& pos);
	virtual float radius();

	GameObject();
	~GameObject();

	CC_SYNTHESIZE(int, _hp, HP);
	CC_SYNTHESIZE(int, _maxHp, MaxHP);
	CC_SYNTHESIZE(int, _atk, Atk);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(std::string, _stateID, StateID);
	CC_SYNTHESIZE(cocos2d::CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _vector, Vector);

protected:

	MainScene *_main;
	HudLayer *_hud;
	ObjectManager *_om;

	void setStateID();
	bool isNormalState();
	bool isEnemyState();
	bool isResultState();

};


#endif /* defined(__WillYard__GameObject__) */
