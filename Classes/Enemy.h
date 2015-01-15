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
#include "ObjectManager.h"
//#include "Player.h"

class MainScene;
class Player;

enum enemyType
{
	kTag_rat1 = 1,
	kTag_rat2,
	kTag_vampire,
	kTag_enemyLength,

};

class Enemy : public GameObject {
private:

	ObjectManager *_om;

	Player *_wisp;

	Enemy* initEnemy(enemyType type, float xPos, float yPos);

	void attackCheck();
	void onEnemyStateEnter();
	int randomAttack(int value);
	cocos2d::CCRect setEnemyRect();
	bool isContanctWithContacted(bool isContact);
	bool isDeadWithAttacking();
	void normalDamage(int playerAtk);
	void overDamage();
	bool isNormalState();
	bool isEnemyState();
	bool isResultState();

public:

	virtual void onStateEnter();
	virtual void onStateExit();
	virtual void stateUpdate(float dt);
	virtual void damage();
	void died();

	static Enemy* create(enemyType type, float xPos, float yPos);
	void attack();
	bool isDeadOrAttacked();
	void hitCheck();
	void initAnimation();
	void resultExit();
	std::string fileNameInit(enemyType type);
	void animationInit(enemyType type);
	int calcRandom(int min, int max);

	CC_SYNTHESIZE(bool, _isAttacked, IsAttacked);
	CC_SYNTHESIZE(bool, _isContacted, IsContacted);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(enemyType, _eType, Etype);
	
	Enemy(MainScene *main);
	~Enemy(void);
};

#endif /*defined(__WillYard__Enemy__)*/
