/*
* EnemyRatOne.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyRatOne__
#define __WillYard__EnemyRatOne__

#include "Enemy.h"

class EnemyRatOne : public Enemy
{
public:
	
	/**	�GNPC�𐶐�
	*	@param xPos �ݒu������W�ix���j
	*	@param yPos �ݒu������W�iy���j
	*	@return	�GNPC
	*/
	static EnemyRatOne* create(float xPos, float yPos);
	
private:

	Enemy* activateSettings(Enemy *enemy, float xPos, float yPos) override;

	EnemyRatOne();
	~EnemyRatOne();

};

#endif /* defined(__WillYard__EnemyRatOne__) */