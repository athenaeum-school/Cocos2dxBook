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

class Player;

class EnemyHit : public GameObject
{
public:
	/**
	* @param m_isContacted
	* �d�������蔻���h�����߂̃t���O
	*/
	CC_SYNTHESIZE(bool, m_isContacted, IsContacted);

	void damage();

protected:

	Player *m_pWisp;

	void hitCheck();
	cocos2d::CCRect setEnemyRect();

	/**	�����蔻��
	*	@param isContact_interSects	���g�̓����蔻��Ƀv���C���[���G��Ă��邩
	*	@return	�GNPC�ɐG���A���̐ڐG�܂łɐG��Ă��Ȃ���ΐ^
	*/
	bool isContanctWithContacted(bool isContact_interSects);

	/**	�����蔻��
	*	@return	�GNPC���������Ă��āA�v���C���[���U�����Ȃ�ΐ^
	*/
	bool isAliveWithAttacking();
	
	void normalDamage(int playerAtk);
	void overDamage();
	void died();
	
	EnemyHit();
	~EnemyHit();

};

#endif /*defined(__WillYard__EnemyHit__)*/
