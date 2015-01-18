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
	//エネミー生成
	EnemyRatTwo * enemy = new EnemyRatTwo();
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

std::string EnemyRatTwo::statusInit(enemyType type)
{
	std::string fileName;
	//エネミータイプに応じて、ステータスを設定
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