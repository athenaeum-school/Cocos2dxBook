/*
* EnemyFactory.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyFactory__
#define __WillYard__EnemyFactory__


#include "Enemy.h"

class Enemy;
enum enemyType;

class EnemyFactory : public cocos2d::CCNode
{
public:

	Enemy* createEnemy(enemyType type, float xPos, float yPos);

	CREATE_FUNC(EnemyFactory);

	EnemyFactory();
	~EnemyFactory();
};

#endif /* defined(__WillYard__EnemyFactory__) */