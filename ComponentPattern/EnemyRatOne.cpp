/*
* EnemyRatOne.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyRatOne.h"
#include "MainScene.h"
#include "HudLayer.h"

const int RAT_ONE_HP = 50;
const int RAT_ONE_MAXHP = 50;
const int RAT_ONE_ATKPOWER = 5;

EnemyRatOne::EnemyRatOne(){}

EnemyRatOne::~EnemyRatOne(){}

EnemyRatOne* EnemyRatOne::create(enemyType type, float xPos, float yPos)
{
	//�G�l�~�[����
	EnemyRatOne * enemy = new EnemyRatOne();
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

std::string EnemyRatOne::initStatus(enemyType type)
{
	std::string fileName;
	//�G�l�~�[�^�C�v�ɉ����āA�X�e�[�^�X��ݒ�
	fileName = "enemy_rat1.png";
	this->setEnemyType(type);
	this->setHP(RAT_ONE_HP);
	this->setMaxHP(RAT_ONE_MAXHP);
	this->setAtkPower(RAT_ONE_ATKPOWER);
	
	return fileName;
}

void EnemyRatOne::setIdleAction()
{
	//HudLayer�̃C���X�^���X���Ăяo��
	//�ҋ@�A�N�V����
	Hud::getInstance()->getAction()->enemyIdleAction(this, -0.2, 0.2);
}