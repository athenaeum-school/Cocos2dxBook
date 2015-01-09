/*
* EnemyState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyState__
#define __WillYard__EnemyState__


#include "GameState.h"
#include <cocos2d.h>
#include "Player.h"
#include "Enemy.h"


class EnemyState : public GameState
{
public:
	virtual void stateUpdate(float dt);
	virtual bool onStateEnter();
	virtual bool onStateExit();
	virtual bool onTouchBeganEvent();
	virtual void onTouchMovedEvent();
	virtual void onTouchEndedEvent();
	virtual void onInputEvent(cocos2d::CCPoint* pts);

	virtual std::string getStateID() { return s_enemyID; }

	EnemyState();
	~EnemyState();

private:

	static const std::string s_enemyID;
	static void s_enemyToNormal();
	static void s_enemyToIdle();

};

#endif /* defined(__WillYard__EnemyState__) */
