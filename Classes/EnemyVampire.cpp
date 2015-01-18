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


EnemyVampire::EnemyVampire(){}

EnemyVampire::~EnemyVampire(){}


EnemyVampire* EnemyVampire::create(enemyType type, float xPos, float yPos)
{
	//�G�l�~�[����
	EnemyVampire * enemy = new EnemyVampire();
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

std::string EnemyVampire::statusInit(enemyType type)
{
	std::string fileName;
	//�G�l�~�[�^�C�v�ɉ����āA�X�e�[�^�X��ݒ�
	fileName = "enemy_vampire.png";
	this->setEtype(type);
	this->setHP(100);
	this->setMaxHP(100);
	this->setAtk(20);
	this->setAddMapName("vampire");

	return fileName;
}

void EnemyVampire::setIdleAction()
{
	_hud->getAnime()->enemy_vamp_idleAnime(this);
}