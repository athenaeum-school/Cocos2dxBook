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
const int RAT_ONE_ATK = 5;

EnemyRatOne::EnemyRatOne(){}

EnemyRatOne::~EnemyRatOne(){}

EnemyRatOne* EnemyRatOne::create(float xPos, float yPos)
{
	//�G�l�~�[����
	EnemyRatOne * enemy = new EnemyRatOne();
	if (enemy)
	{
		enemy->initWithFile("enemy_rat1.png");
		enemy = static_cast<EnemyRatOne *>(enemy->activateSettings(xPos, yPos));
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

Enemy* EnemyRatOne::activateSettings(float xPos, float yPos)
{
	//Enemy�N���X�́AinitEnemy(),initStatus(),setIdleAction()���Ăяo���A
	//�GNPC�̐ݒ������
	this->initStatus(kTag_rat1, RAT_ONE_HP, RAT_ONE_MAXHP, RAT_ONE_ATK);
	this->initEnemy(xPos, yPos);
	this->setIdleAction(-0.2, 0.2);
	return this;
}
