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


class PlayerHit : public GameObject {
private:

	bool gThanRadius(float wispNextPos);
	bool lessThanRadius(float wispNextPos, float screenwh);
	cocos2d::CCRect enemyAtkRect(EnemyAttack *enemyAttack);
	
protected:

	void hitCheck();
	void damage(EnemyAttack *atk);
	
	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();

	PlayerHit();
	~PlayerHit();

};

#endif /*defined(__WillYard__PlayerHit__)*/