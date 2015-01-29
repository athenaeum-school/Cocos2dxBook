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
	*	@return	�GNPC
	*/
	static EnemyRatTwo* create(enemyType type, float xPos, float yPos);

private:

	/**	�GNPC�̉摜�ƃX�e�[�^�X�ݒ�
	*	@param type �GNPC�̎��
	*	@return	�摜�t�@�C����
	*/
	std::string statusInit(enemyType type) override;

	//�ҋ@���̃A�N�V����
	void setIdleAction() override;

	EnemyRatTwo();
	~EnemyRatTwo();

};

#endif /* defined(__WillYard__EnemyRatTwo__) */