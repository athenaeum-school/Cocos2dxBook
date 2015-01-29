/*
* PlayerHit.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__PlayerHit__
#define __WillYard__PlayerHit__

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyAttack.h"

class PlayerHit : public GameObject 
{
protected:

	void hitCheck();
	void damage(EnemyAttack *atk);
	void died();
	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();

	PlayerHit();
	~PlayerHit();

private:

	cocos2d::CCRect enemyAtkRect(EnemyAttack *enemyAttack);
	bool isLessThanRadius(float wispNextPos);
	bool isGreaterThanRadius(float wispNextPos, float screenwh);
	
};

#endif /*defined(__WillYard__PlayerHit__)*/