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
#include "EnemyHit.h"

enum enemyType
{
	kTag_rat1 = 1,
	kTag_rat2,
	kTag_vampire,
	kTag_enemyLength,

};

class Enemy : public EnemyHit 
{

public:

	CC_SYNTHESIZE(bool, _isAttacked, IsAttacked);
	CC_SYNTHESIZE(enemyType, _eType, Etype);
	CC_SYNTHESIZE(std::string, _addMapName, AddMapName);

	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
protected:

	virtual Enemy* initEnemy(enemyType type, float xPos, float yPos);
	virtual std::string statusInit(enemyType type) = 0;
	virtual void setIdleAction() = 0;

	Enemy();
	~Enemy(void);

private:
	
	void onEnemyStateEnter();
	int randomAttack(int value);
	int calcRandom(int min, int max);
	void attack();
	bool isDeadOrAttacked();
	void resultExit();
	
};

#endif /*defined(__WillYard__Enemy__)*/
