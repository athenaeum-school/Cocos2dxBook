/*
* EnemyVampire.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyVampire.h"
#include "MainScene.h"
#include "HudLayer.h"

const int VAMPIRE_HP = 120;
const int VAMPIRE_MAXHP = 120;
const int VAMPIRE_ATKPOWER = 20;

EnemyVampire::EnemyVampire(){}

EnemyVampire::~EnemyVampire(){}

EnemyVampire* EnemyVampire::create(float xPos, float yPos)
{
	//�G�l�~�[����
	EnemyVampire * enemy = new EnemyVampire();
	if (enemy)
	{
		enemy->initWithFile("enemy_vampire.png");
		enemy = static_cast<EnemyVampire *>(enemy->activateSettings(xPos, yPos));
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

Enemy* EnemyVampire::activateSettings(float xPos, float yPos)
{
	//Enemy�N���X�́AinitEnemy(),initStatus(),setIdleAction()���Ăяo���A
	//�GNPC�̐ݒ������
	this->initStatus(kTag_vampire, VAMPIRE_HP, VAMPIRE_MAXHP, VAMPIRE_ATKPOWER);
	this->initEnemy(xPos, yPos);
	this->setIdleAction(0.2, -0.2);
	return this;
}