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
		Main::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autorelease���g�p���Ă��邽�߁Adelete�̑���Ɏg�p�A���������J��
	//���x���������Ȃ��悤�ɃK�[�h��������
	CC_SAFE_DELETE(enemy);
	return NULL;
}

std::string EnemyRatOne::statusInit(enemyType type)
{
	std::string fileName;
	//�G�l�~�[�^�C�v�ɉ����āA�X�e�[�^�X��ݒ�
	fileName = "enemy_rat1.png";
	this->setEtype(type);
	this->setHP(30);
	this->setMaxHP(30);
	this->setAtk(5);
	this->setAddMapName("rat1");

	return fileName;
}

void EnemyRatOne::setIdleAction()
{
		_hud->getAnime()->enemyIdleAnime(this);
}