/*
* EnemyVampire.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyVampire__
#define __WillYard__EnemyVampire__

#include "Enemy.h"

class EnemyVampire : public Enemy
{
public:

	/**	�GNPC�𐶐�
	*	@param type �GNPC�̎��
	*	@param xPos �ݒu������W�ix���j
	*	@param yPos �ݒu������W�iy���j
	*	@return	�GNPC
	*/
	static EnemyVampire* create(float xPos, float yPos);

private:

	Enemy* activateSettings(Enemy *enemy, float xPos, float yPos) override;

	EnemyVampire();
	~EnemyVampire();

};

#endif /* defined(__WillYard__EnemyVampire__) */