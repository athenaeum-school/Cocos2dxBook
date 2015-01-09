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
	
	static Enemy* create(const char* fileName, float xPos, float yPos);
	void attack();
	bool isEnemyState();
	void hitCheck();
	void starEffect();
	void swingEffect();
	void explodeEffect();
	void damageEffect();

	CC_SYNTHESIZE(bool, _isHit, IsHit);
	
	Enemy(MainScene *main);
	~Enemy(void);
};

#endif /*defined(__WillYard__Enemy__)*/
