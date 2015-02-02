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

	/**	�GNPC�𐶐�
	*	@param type �GNPC�̎��
	*	@param xPos �ݒu������W�ix���j
	*	@param yPos �ݒu������W�iy���j
	*	@return	�GNPC
	*/
	Enemy* createEnemy(enemyType type, float xPos, float yPos);

private:

	EnemyFactory();
	~EnemyFactory();

};

#endif /* defined(__WillYard__EnemyFactory__) */