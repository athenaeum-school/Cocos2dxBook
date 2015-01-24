/*
* Player.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__Player__
#define __WillYard__Player__

#include "cocos2d.h"
#include "PlayerHit.h"

class Player : public PlayerHit
{
public:
	
	CC_SYNTHESIZE(bool, m_canFire, CanFire);
	CC_SYNTHESIZE(bool, m_isAttacking, IsAttacking);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_force, Force);
	CC_SYNTHESIZE(int, m_timer, Timer);
	
	static Player* create();

	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	/**	�U���͂�������
	*	@param power �v���C���[�̍U����
	*/
	void addPower(int power);

	/**	�U���͂����炷
	*	@param power �v���C���[�̍U����
	*/
	void drawPower(int power);

	//�V���b�g��A�^�C�}�[�X�^�[�g
	void startTimer();

	//���g���C��̍Đݒ�
	void resetWisp();

private:

	float m_angle;

	//�v���C���[�̏����ݒ�
	Player* initWisp();

	//���������̉^���ʂ��v���C���[�ɉ�����
	void addForceToWisp();

	/**	
	*	@return �^�b�`�C���[�W�ɐG��Ă����玟�̏�����
	*/
	bool isNext();

	/**	�K�C�h�����쐬
	*	@param movePoint �^�b�`���̍��W
	*/
	void createArrow(cocos2d::CCPoint movePoint);

	/**	�K�C�h���̊p�x���v�Z
	*	@param arrow ���I�u�W�F�N�g
	*	@param movePoint �^�b�`���̍��W
	*/
	void arrowSettings(cocos2d::CCSprite *arrow, cocos2d::CCPoint movePoint);

	/**	�v���C���[�ɉ����x��������i�p�x�̕␳���s�Ȃ��j
	*	@param endPoint ���������̃^�b�`���W
	*	@return �������
	*/
	cocos2d::CCPoint calcForce(cocos2d::CCPoint endPoint);
	
	Player();
	~Player();

};

#endif /*defined(__WillYard__Player__)*/
