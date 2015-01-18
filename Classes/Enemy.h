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


class MainScene;
class Player;


enum enemyType
{
	kTag_rat1 = 1,
	kTag_rat2,
	kTag_vampire,
	kTag_enemyLength,

};


class Enemy : public GameObject 
{

public:

	CC_SYNTHESIZE(bool, _isAttacked, IsAttacked);
	CC_SYNTHESIZE(bool, _isContacted, IsContacted);
	//CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(enemyType, _eType, Etype);
	CC_SYNTHESIZE(std::string, _addMapName, AddMapName);

	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	void damage();
	
protected:

	virtual Enemy* initEnemy(enemyType type, float xPos, float yPos);
	virtual std::string statusInit(enemyType type) = 0;
	virtual void setIdleAction() = 0;

	Enemy();
	~Enemy(void);

private:

	Player *_wisp;

	void onEnemyStateEnter();
	int randomAttack(int value);
	cocos2d::CCRect setEnemyRect();
	bool isContanctWithContacted(bool isContact);
	bool isDeadWithAttacking();
	void normalDamage(int playerAtk);
	void overDamage();
	void died();
	void attack();
	bool isDeadOrAttacked();
	void hitCheck();
	void resultExit();
	int calcRandom(int min, int max);
	
};

#endif /*defined(__WillYard__Enemy__)*/
