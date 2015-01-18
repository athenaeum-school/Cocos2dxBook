/*
* EnemyVampire.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyVampire__
#define __WillYard__EnemyVampire__

#include "Enemy.h"

class EnemyVampire : public Enemy
{
public:

	static EnemyVampire* create(enemyType type, float xPos, float yPos);

private:

	std::string statusInit(enemyType type) override;
	void setIdleAction() override;

	EnemyVampire();
	~EnemyVampire();

};

#endif /* defined(__WillYard__EnemyVampire__) */