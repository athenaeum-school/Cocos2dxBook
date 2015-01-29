/*
* EnemyFactory.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyFactory.h"
#include "EnemyRatOne.h"
#include "EnemyRatTwo.h"
#include "EnemyVampire.h"

EnemyFactory::EnemyFactory(){}

EnemyFactory::~EnemyFactory(){}

Enemy* EnemyFactory::createEnemy(enemyType type, float xPos, float yPos)
{
	Enemy *enemy = NULL;

	if (type == kTag_rat1) 
	{
		enemy = EnemyRatOne::create(xPos, yPos);
	}
	else if (type == kTag_rat2) 
	{
		enemy = EnemyRatTwo::create(xPos, yPos);
	}
	else if (type == kTag_vampire) 
	{
		enemy = EnemyVampire::create(xPos, yPos);
	}
	
	return enemy;
}