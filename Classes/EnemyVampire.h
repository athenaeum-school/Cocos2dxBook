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
	static EnemyVampire* create(enemyType type, float xPos, float yPos);

private:

	/**	�GNPC�̉摜�ƃX�e�[�^�X�ݒ�
	*	@param type	�GNPC�̎��
	*	@return	�摜�t�@�C����
	*/
	std::string statusInit(enemyType type) override;

	//�ҋ@���̃A�N�V����
	void setIdleAction() override;

	EnemyVampire();
	~EnemyVampire();

};

#endif /* defined(__WillYard__EnemyVampire__) */