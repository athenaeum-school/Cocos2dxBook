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
#include "GameObject.h"
#include "Enemy.h"

class MainScene;

class EnemyAttack : public cocos2d::CCSprite {
private:

	EnemyAttack* initEnemyAttack(const char* fileName, cocos2d::CCPoint point);

public:

	CC_SYNTHESIZE(int, _atk, Atk);
	CC_SYNTHESIZE(float, _destroyTimer, DestroyTimer);

	static EnemyAttack* create(const char* fileName, cocos2d::CCPoint point);
	void attack(Enemy *enemy);

	EnemyAttack();
	~EnemyAttack(void);
};

#endif /*defined(__WillYard__EnemyAttack__)*/
