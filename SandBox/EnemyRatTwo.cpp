/*
* EnemyRatTwo.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyRatTwo.h"
#include "MainScene.h"
#include "HudLayer.h"

const int RAT_TWO_HP = 80;
const int RAT_TWO_MAXHP = 80;
const int RAT_TWO_ATKPOWER = 10;

EnemyRatTwo::EnemyRatTwo(){}

EnemyRatTwo::~EnemyRatTwo(){}

EnemyRatTwo* EnemyRatTwo::create(enemyType type, float xPos, float yPos)
{
	//�G�l�~�[����
	EnemyRatTwo * enemy = new EnemyRatTwo();
	if (enemy)
	{
		enemy->initEnemy(type, xPos, yPos);
		enemy->autorelease();
		//MainScene�̃C���X�^���X���Ăяo���A�����ɒǉ�
		MS::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autorelease���g�p���Ă��邽�߁Adelete�̑���Ɏg�p�A���������J��
	//���x���������Ȃ��悤�ɃK�[�h��������
	CC_SAFE_DELETE(enemy);
	return NULL;
}

std::string EnemyRatTwo::initStatus(enemyType type)
{
	std::string fileName;
	//�G�l�~�[�^�C�v�ɉ����āA�X�e�[�^�X��ݒ�
	fileName = "enemy_rat2.png";
	this->setEnemyType(type);
	this->setHP(RAT_TWO_HP);
	this->setMaxHP(RAT_TWO_MAXHP);
	this->setAtkPower(RAT_TWO_ATKPOWER);

	return fileName;
}

void EnemyRatTwo::setIdleAction()
{
	//HudLayer�̃C���X�^���X���Ăяo��
	//�ҋ@�A�N�V����
	Hud::getInstance()->getAction()->enemyIdleAction(this, -0.2, 0.2);
}