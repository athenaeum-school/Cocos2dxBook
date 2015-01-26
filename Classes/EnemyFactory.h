/*
* EnemyFactory.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyFactory__
#define __WillYard__EnemyFactory__

#include "Enemy.h"

class Enemy;
enum enemyType;

class EnemyFactory : public cocos2d::CCNode
{
public:

	CREATE_FUNC(EnemyFactory);

	/**	敵NPCを生成
	*	@param type 敵NPCの種類
	*	@param xPos 設置する座標（x軸）
	*	@param yPos 設置する座標（y軸）
	*	@return	敵NPC
	*/
	Enemy* createEnemy(enemyType type, float xPos, float yPos);

private:

	EnemyFactory();
	~EnemyFactory();

};

#endif /* defined(__WillYard__EnemyFactory__) */