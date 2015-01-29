/*
* PlayerHit.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__PlayerHit__
#define __WillYard__PlayerHit__

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyAttack.h"

class PlayerHit : public GameObject 
{
protected:
	
	//�GNPC�̍U���Ƃ̏Փ˔���
	void hitCheck();

	/**	�_���[�W����
	*	@param atkPower �GNPC�̍U����
	*/
	void damage(EnemyAttack *atkPower);

	//�s�k����
	void died();

	//������k�̕ǂ̏Փ˔���
	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();

	//�Փ˂Ɋւ���֐���h���N���X�ł܂Ƃ߂ČĂяo���������z�֐�
	virtual void activateCollision() = 0;

	PlayerHit();
	~PlayerHit();

private:

	/**	�GNPC�̍U���̕`��̈���v�Z
	*	@param enemyAttack �GNPC�̍U��
	*/
	cocos2d::CCRect enemyAtkRect(EnemyAttack *enemyAttack);

	/**	�ǂƂ̏Փ˂𔻒�i��A���j
	*	@param wispNextPos �v���C���[�̈ړ���
	*/
	bool isLessThanRadius(float wispNextPos);

	/**	�ǂƂ̏Փ˂𔻒�i�k�A���j
	*	@param wispNextPos �v���C���[�̈ړ���
	*	@param screenwh ��ʃT�C�Y�̉����ƍ���
	*/
	bool isGreaterThanRadius(float wispNextPos, float screenwh);
	
};

#endif /*defined(__WillYard__PlayerHit__)*/