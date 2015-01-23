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
const int VAMPIRE_ATK = 20;

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
		MS::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
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
	this->setHP(VAMPIRE_HP);
	this->setMaxHP(VAMPIRE_MAXHP);
	this->setAtkPower(VAMPIRE_ATK);
	
	return fileName;
}

void EnemyVampire::setIdleAction()
{
	//�ҋ@�A�N�V����
	Hud::getInstance()->getAnime()->enemy_vamp_idleAnime(this);
}