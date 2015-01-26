/*
* NormalState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__NormalState__
#define __WillYard__NormalState__

#include "GameState.h"
#include <cocos2d.h>
#include "Player.h"
#include "Enemy.h"

class NormalState : public GameState
{
public:
	//�v�Z�p�����o�[
	CC_SYNTHESIZE(cocos2d::CCPoint, m_wispVector, WispVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_wispNextPosition, WispNextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_enemyNextPosition, EnemyNextPosition);

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

    std::string getStateID() override { return s_normalID; }
	
    NormalState();
    ~NormalState();

private:
   
	Player *m_pWisp;
    static const std::string s_normalID;
    
	void normalToEnemy();
	void normalToResult();

	//���̏�Ԃ𔻒f����
    void switchState();

	/**	ObjectManager�̃��C�hHP��0�ȉ����m�F
	*	@return	�^�U
	*/
	bool isRaidHpLessThanZero();

	/**	�E�B�X�v�̃^�C�}�[��0�ȏォ�m�F
	*	@return	�^�U
	*/
	bool isGreaterThanCount(int count);

	//�����Փ˔���̂��߂̌v�Z
	void calcCollision();

	/**	�E�B�X�v�̃^�C�}�[��0�ȏォ�m�F
	*	@param distOne �E�B�X�v�̎���x�Ay���W�ƁA�GNPC�̌��݂�x�Ay���W�̋��������ꂼ��Q�悵�A����x��y�̘a
	*	@param distTwo �E�B�X�v�̌��݂�x�Ay���W�ƁA�GNPC�̎���x�Ay���W�̋��������ꂼ��Q�悵�A����x��y�̘a
	*	@param enemy �GNPC 
	*/
	void onCollisionFast(float distOne, float distTwo, float radius, Enemy *enemy);

	/**	//���������a�ȉ����m�F
	*	@param dist onCollisionFast()��distOne�܂���distTwo
	*	@param radius �GNPC�A�E�B�X�v�̔��a�𑫂��A2�悵���l�܂���0
	*	@return	�^�U
	*/
	bool isLessThanRadius(float dist, float radius);

	/**	�GNPC�Ƃ̋������Z�o
	*	@param nextPos �E�B�X�v�̖ڕW���W
	*	@param getPos �GNPC�̌��ݍ��W
	*	@return �����i�E�B�X�v�̖ڕW���W - �GNPC�̌��ݍ��W�j
	*/
	float calcDiff(float nextPos, float getPos);

	/**	�a���v�Z
	*	@param powOne x���̋���
	*	@param powTwo y���̋���
	*	@return �a
	*/
	float calcSum(float powOne, float powTwo);

	/**	�Փ˔���
	*	@param enemy �GNPC
	*	@return �Փ˂���̈�
	*/
	float calcVector(Enemy *enemy);
	
};


#endif /* defined(__WillYard__NormalState__) */
