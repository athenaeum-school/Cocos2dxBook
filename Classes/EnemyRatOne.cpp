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
	//エネミー生成
	EnemyRatOne * enemy = new EnemyRatOne();
	if (enemy)
	{
		enemy->initEnemy(type, xPos, yPos);
		enemy->autorelease();
		Main::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

std::string EnemyRatOne::statusInit(enemyType type)
{
	std::string fileName;
	//エネミータイプに応じて、ステータスを設定
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