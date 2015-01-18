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
		Main::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autorelease���g�p���Ă��邽�߁Adelete�̑���Ɏg�p�A���������J��
	//���x���������Ȃ��悤�ɃK�[�h��������
	CC_SAFE_DELETE(enemy);
	return NULL;
}

std::string EnemyRatTwo::statusInit(enemyType type)
{
	std::string fileName;
	//�G�l�~�[�^�C�v�ɉ����āA�X�e�[�^�X��ݒ�
	fileName = "enemy_rat2.png";
	this->setEtype(type);
	this->setHP(60);
	this->setMaxHP(60);
	this->setAtk(10);
	this->setAddMapName("rat2");

	return fileName;
}

void EnemyRatTwo::setIdleAction()
{
	_hud->getAnime()->enemyIdleAnime(this);
}