/*
* EnemyAttack.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyAttack__
#define __WillYard__EnemyAttack__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyAttack : public cocos2d::CCSprite 
{
public:

	CC_SYNTHESIZE(int, m_atkPower, AtkPower);

	/**	�GNPC�̍U���𐶐�
	*	@param enemy �U�����s�Ȃ�NPC
	*	@return	�������ꂽ�U��
	*/
	static EnemyAttack* create(Enemy *enemy);
	
	/**	�GNPC�̍U��
	*	@param enemy �U�����s�Ȃ�NPC
	*/
	void attack(Enemy *enemy);

	EnemyAttack();
	~EnemyAttack();

private:

	/**	�U���̉摜�t�@�C�����w��
	*	@param type �GNPC�̎��
	*	@return	��ʂɉ������U���̉摜�t�@�C����
	*/
	std::string initFileName(enemyType type);

	/**	�U���̈ʒu�ƃt�@�C������ݒ�
	*	@param enemy �U�����s�Ȃ��GNPC
	*	@param point �GNPC�̍��W�i�U���������W�j
	*	@return	�ݒ肳�ꂽ�U��
	*/
	EnemyAttack* initEnemyAttack(Enemy *enemy, cocos2d::CCPoint point);

};

#endif /*defined(__WillYard__EnemyAttack__)*/
