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

class EnemyState : public GameState
{
public:

	void stateUpdate(float dt) override;
	bool onStateEnter() override;
	bool onStateExit() override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

	std::string getStateID() override { return s_enemyID; }

	EnemyState();
	~EnemyState();

private:

	int m_timer;
	bool m_isTurn;
	Player *m_pWisp;

	static const std::string s_enemyID;

	void enemyToNormal();
	void enemyToResult();
	void turnOnEnemy();
	void setIsTurn();
	void switchState();
	bool isGreaterThanCount(int count);
	
};

#endif /* defined(__WillYard__EnemyState__) */
