/*
* EnemyHit.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyHit__
#define __WillYard__EnemyHit__

#include "cocos2d.h"
#include "GameObject.h"

class EnemyHit : public GameObject
{
public:

	//�d�������蔻���h�����߂̃t���O
	CC_SYNTHESIZE(bool, m_isContacted, IsContacted);

	//�_���[�W����
	void damage();
	
protected:

	//�����蔻��̑�������
	void hitCheck();

	/**	�����蔻��p�̏���
	*	@return �GNPC�̃_���[�W����`��̈�
	*/
	cocos2d::CCRect setEnemyRect();

	/**	�����蔻��p�̏���
	*	@param isContact_interSects	�GNPC�̓����蔻��Ƀv���C���[���G��Ă��邩
	*	@return �GNPC�ɐG���A���̐ڐG�܂łɐG��Ă��Ȃ���ΐ^
	*/
	bool isContanctWithContacted(bool isContact_interSects);

	/**	�����蔻��p�̏���
	*	@return �GNPC���������Ă��āA�v���C���[���U�����Ȃ�ΐ^
	*/
	bool isAliveWithAttacking();
	
	/**	�ʏ�_���[�W����
	*	@param AtkPower �v���C���[�̍U����
	*/
	void normalDamage(int PlayerAtkPower);

	//HP�ȏ�̃_���[�W���󂯂Ȃ��悤�ɂ���
	void overDamage();

	//���S����
	void died();
	
	EnemyHit();
	~EnemyHit();

};

#endif /*defined(__WillYard__EnemyHit__)*/
