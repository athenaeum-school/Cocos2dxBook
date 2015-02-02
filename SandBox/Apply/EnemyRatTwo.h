/*
* EnemyRatTwo.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyRatTwo__
#define __WillYard__EnemyRatTwo__

#include "Enemy.h"

class EnemyRatTwo : public Enemy
{
public:

	/**	�GNPC�𐶐�
	*	@param type �GNPC�̎��
	*	@param xPos �ݒu������W�ix���j
	*	@param yPos �ݒu������W�iy���j
	*	@return �GNPC
	*/
	static EnemyRatTwo* create(float xPos, float yPos);

private:

	/**	Enemy�N���X�́AinitEnemy(),initStatus(),setIdleAction()���Ăяo���A
	*	�GNPC�̐ݒ�����鏃�����z�֐�
	*	@param xPos �GNPC��x���z�u���W
	*	@param yPos �GNPC��y���z�u���W
	*/
	void activateSettings(float xPos, float yPos) override;

	EnemyRatTwo();
	~EnemyRatTwo();

};

#endif /* defined(__WillYard__EnemyRatTwo__) */