/*
* EnemyHit.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyHit__
#define __WillYard__EnemyHit__

#include "cocos2d.h"
#include "GameObject.h"

class MainScene;
class Player;

class EnemyHit : public GameObject
{

public:

	CC_SYNTHESIZE(bool, _isContacted, IsContacted);

	void damage();

protected:

	Player *_wisp;

	cocos2d::CCRect setEnemyRect();
	bool isContanctWithContacted(bool isContact);
	bool isDeadWithAttacking();
	void normalDamage(int playerAtk);
	void overDamage();
	void died();
	void hitCheck();

	EnemyHit();
	~EnemyHit();

};

#endif /*defined(__WillYard__EnemyHit__)*/