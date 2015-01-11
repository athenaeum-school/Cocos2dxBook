/*
* Enemy.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__Enemy__
#define __WillYard__Enemy__

#include "cocos2d.h"
#include "GameObject.h"

class MainScene;

class Enemy : public GameObject {
private:

	Enemy* initEnemy(const char* fileName, float xPos, float yPos);

public:

	virtual void stateUpdate(float dt);
	virtual void damage();
	virtual void died();

	static Enemy* create(const char* fileName, int hp, float xPos, float yPos);
	void attack();
	bool isEnemyState();
	bool isDeadOrAttacked();
	void hitCheck();
	void starEffect();
	void swingEffect();
	void explodeEffect();
	void damageEffect();
	void diedEffect();
	void initAnimation();

	CC_SYNTHESIZE(bool, _isAttacked, IsAttacked);
	CC_SYNTHESIZE(bool, _isContacted, IsContacted);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	
	Enemy(MainScene *main, int hp);
	~Enemy(void);
};

#endif /*defined(__WillYard__Enemy__)*/
