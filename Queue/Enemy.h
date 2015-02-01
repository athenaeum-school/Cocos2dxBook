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

//�GNPC�̎��
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

	CC_SYNTHESIZE(bool, m_isAttacked, IsAttacked);
	CC_SYNTHESIZE(enemyType, m_enemyType, EnemyType);
	
	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
protected:

	/**	�GNPC�����ݒ�
	*	@param type	�GNPC�̎��
	*	@param xPos	�z�u����x���̍��W
	*	@param yPos	�z�u����y���̍��W
	*	@return	�������ꂽ�GNPC
	*/
	virtual Enemy* initEnemy(enemyType type, float xPos, float yPos);


	/**	�GNPC�̉摜�ƃX�e�[�^�X�ݒ�i�h���N���X�Ŏ������鏃�����z�֐��j
	*	@param type	�GNPC�̎��
	*	@return	�摜�t�@�C����
	*/
	virtual std::string initStatus(enemyType type) = 0;

	//�ҋ@���̃A�N�V�����i�h���N���X�Ŏ������鏃�����z�֐��j
	virtual void setIdleAction() = 0;

	Enemy();
	~Enemy(void);

private:
	
	/**	�GNPC�̍U�������m��
	*	@param value �GNPC�̑����ɏ�Z����l
	*	@return	�GNPC�̑��� % (�GNPC�̑��� * value)
	*/
	int randomAttack(int value);

	/**	min~max�̒l�𐮐��ŕԂ�
	*	@param min �ŏ��l
	*	@param max �ő�l
	*	@return	min~max�Ԃ̗���
	*/
	int calcRandom(int min, int max);

	//�U�����s�Ȃ�
	void attack();

};

#endif /*defined(__WillYard__Enemy__)*/
