/*
* EnemyRatOne.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyRatOne__
#define __WillYard__EnemyRatOne__

#include "Enemy.h"

class EnemyRatOne : public Enemy
{
public:
	
	static EnemyRatOne* create(enemyType type, float xPos, float yPos);

private:

	std::string statusInit(enemyType type) override;
	void setIdleAction() override;

	EnemyRatOne();
	~EnemyRatOne();

};

#endif /* defined(__WillYard__EnemyRatOne__) */