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

const int VAMPIRE_HP = 1;
const int VAMPIRE_MAXHP = 120;
const int VAMPIRE_ATK = 20;

EnemyVampire::EnemyVampire(){}

EnemyVampire::~EnemyVampire(){}

EnemyVampire* EnemyVampire::create(float xPos, float yPos)
{
	//エネミー生成
	EnemyVampire * enemy = new EnemyVampire();
	if (enemy)
	{
		enemy->initWithFile("enemy_vampire.png");
		enemy = static_cast<EnemyVampire *>(enemy->activateSettings(enemy, xPos, yPos));
		enemy->autorelease();
		//MainSceneのインスタンスを呼び出し、そこに追加
		MS::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* EnemyVampire::activateSettings(Enemy *enemy, float xPos, float yPos)
{
	this->initStatus(kTag_vampire, VAMPIRE_HP, VAMPIRE_MAXHP, VAMPIRE_ATK);
	this->initEnemy(xPos, yPos);
	this->setIdleAction(0.2, -0.2);
	return this;
}