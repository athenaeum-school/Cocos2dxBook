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
#include "MainScene.h"


class EnemyState : public GameState
{
public:

	virtual void stateUpdate(float dt);
	virtual bool onStateEnter();
	virtual bool onStateExit();
	virtual bool onTouchBeganEvent();
	virtual void onTouchMovedEvent();
	virtual void onTouchEndedEvent();
	
	virtual std::string getStateID() { return s_enemyID; }

	EnemyState();
	~EnemyState();

private:

	int _timer;
	bool _isTurn;
	Player *_wisp;

	static const std::string s_enemyID;
	void enemyToNormal();
	void enemyToResult();
	void turnOnEnemy();
	void setIsTurn();
};

#endif /* defined(__WillYard__EnemyState__) */
