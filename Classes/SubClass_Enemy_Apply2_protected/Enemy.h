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
	
	/**	�GNPC�����ݒ�
	*	@param xPos	�z�u����x���̍��W
	*	@param yPos	�z�u����y���̍��W
	*	@return	�������ꂽ�GNPC
	*/
	//virtual Enemy* initEnemy(float xPos, float yPos);

	/**	�GNPC�̉摜�ƃX�e�[�^�X�ݒ�
	*	@param type	�GNPC�̎��
	*	@param hp	�GNPC��HP
	*	@param maxHp �GNPC�̍ő�HP
	*	@param atkPower	�GNPC�̍U����
	*/
	//void initStatus(enemyType type, int hp, int maxHp, int atkPower);

	/**	�GNPC�̑ҋ@�A�N�V�����iy���ɌJ��Ԃ��j
	*	@param start �n�߂ɗh������
	*	@param next	���ɗh������
	*/
	//void setIdleAction(float start, float next);

protected:

	/**	�h���N���X���ŁAinitEnemy(),initStatus(),setIdleAction()���Ăяo���������z�֐�
	*	@param enemy �������ꂽ�GNPC
	*	@param xPos	�GNPC��x���z�u���W
	*	@param yPos �GNPC��y���z�u���W
	*/
	virtual Enemy* activateSettings(Enemy *enemy, float xPos, float yPos) = 0;
	
	/**	�GNPC�����ݒ�
	*	@param xPos	�z�u����x���̍��W
	*	@param yPos	�z�u����y���̍��W
	*	@return	�������ꂽ�GNPC
	*/
	virtual Enemy* initEnemy(float xPos, float yPos);

	/**	�GNPC�̉摜�ƃX�e�[�^�X�ݒ�
	*	@param type	�GNPC�̎��
	*	@param hp	�GNPC��HP
	*	@param maxHp �GNPC�̍ő�HP
	*	@param atkPower	�GNPC�̍U����
	*/
	void initStatus(enemyType type, int hp, int maxHp, int atkPower);

	/**	�GNPC�̑ҋ@�A�N�V�����iy���ɌJ��Ԃ��j
	*	@param start �n�߂ɗh������
	*	@param next	���ɗh������
	*/
	void setIdleAction(float start, float next);

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
	//EnemyHit�N���X��HitCheck()���Ăяo�����z�֐���override
	void activateHitCheck() override;
	/**	���S���Ă��邩�U���ς݂�
	*	@return	�^�U
	*/
	bool isDeadOrAttacked();
	
};

#endif /*defined(__WillYard__Enemy__)*/
