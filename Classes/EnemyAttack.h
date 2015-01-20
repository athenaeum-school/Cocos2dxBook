/*
* EnemyAttack.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyAttack__
#define __WillYard__EnemyAttack__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyAttack : public cocos2d::CCSprite 
{
public:

	CC_SYNTHESIZE(int, _atk, Atk);

	static EnemyAttack* create(Enemy *enemy);
	void attack(Enemy *enemy);

	EnemyAttack();
	~EnemyAttack();

private:

	std::string fileNameInit(enemyType type);
	EnemyAttack* initEnemyAttack(Enemy *enemy, cocos2d::CCPoint point);

};

#endif /*defined(__WillYard__EnemyAttack__)*/
