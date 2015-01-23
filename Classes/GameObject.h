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

class GameObject : public cocos2d::CCSprite
{
public:

	CC_SYNTHESIZE(int, m_hp, HP);
	CC_SYNTHESIZE(int, m_maxHp, MaxHP);
	CC_SYNTHESIZE(int, m_atkPower, AtkPower);
	CC_SYNTHESIZE(bool, m_isDead, IsDead);
	CC_SYNTHESIZE(std::string, m_stateID, StateID);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_acceleration, Acceleration);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCProgressTimer *, m_pHpBar, HpBar);

	virtual void onStateEnter() = 0;
	virtual void onStateExit() = 0;
	virtual void stateUpdate(float dt) = 0;
	
	void setPosition(const cocos2d::CCPoint& pos);
	float radius();

	float getHpRatio();

protected:

	void setStateID();
	bool isNormalState();
	bool isEnemyState();
	bool isResultState();
	void isDeadWithRet();

	GameObject();
	~GameObject();

};


#endif /* defined(__WillYard__GameObject__) */
