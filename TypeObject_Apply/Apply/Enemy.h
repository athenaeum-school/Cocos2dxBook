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

class EnemyTypeObject;

class Enemy : public EnemyHit 
{
public:

	/**	�GNPC�𐶐�
	*	@param enemyTypeObject �p�[�T�[�Őݒ�������GNPC���
	*	@return �GNPC
	*/
	static Enemy* create(EnemyTypeObject *enemyTypeObject);

	CC_SYNTHESIZE(bool, m_isAttacked, IsAttacked);
	CC_SYNTHESIZE(enemyType, m_enemyType, EnemyType);
	
	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
	Enemy();

protected:

	/**	�GNPC�����ݒ�
	*	@param enemyTypeObject �p�[�T�[�Őݒ�������GNPC���
	*/
	void initEnemy(EnemyTypeObject *enemyTypeObject);


	/**	�GNPC�̉摜�ƃX�e�[�^�X�ݒ�
	*	@param enemyTypeObject �p�[�T�[�Őݒ�������GNPC���
	*	@return	�摜�t�@�C����
	*/
	std::string initStatus(EnemyTypeObject *enemyTypeObject);

	//�ҋ@���̃A�N�V����
	void setIdleAction();

	
	virtual ~Enemy();

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

class EnemyTypeObject
{
public:

	/**	�GNPC�̐���
	*	@return	�GNPC
	*/
	Enemy* createEnemy() { return Enemy::create(this); }


	/**	�p�[�T�[�œGNPC�̐ݒ���s�Ȃ�
	*	@param hp �̗�
	*	@param atkPower �U����
	*	@param xPos �z�u���W�ix���j
	*	@param yPos �z�u���W(y��)
	*	@param enemysType �GNPC�̎��	
	*	@param imageID �ݒ肷��摜�t�@�C��
	*/
	EnemyTypeObject(int hp, int atkPower, float xPos, float yPos, int enemysType, std::string &imageID):
		m_hp(hp),
		m_atkPower(atkPower),
		m_xPos(xPos),
		m_yPos(yPos),
		m_enemyType(enemysType),
		m_imageID(imageID)
	{}

	int getHp() { return m_hp; }
	int getAtkPower(){ return m_atkPower; }
	float getXPOS(){ return m_xPos; }
	float getYPOS(){ return m_yPos; }
	int getEnemyType(){ return m_enemyType; }
	const std::string& getimageID(){ return m_imageID; }

private:

	int m_hp;
	int m_atkPower;
	float m_xPos;
	float m_yPos;
	int m_enemyType;
	std::string m_imageID;

};

#endif /*defined(__WillYard__Enemy__)*/
