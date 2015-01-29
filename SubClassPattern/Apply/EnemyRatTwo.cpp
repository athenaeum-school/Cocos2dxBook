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
#include "HudLayer.h"

const int RAT_TWO_HP = 80;
const int RAT_TWO_MAXHP = 80;
const int RAT_TWO_ATK = 10;

EnemyRatTwo::EnemyRatTwo(){}

EnemyRatTwo::~EnemyRatTwo(){}

EnemyRatTwo* EnemyRatTwo::create(float xPos, float yPos)
{
	//エネミー生成
	EnemyRatTwo * enemy = new EnemyRatTwo();
	if (enemy)
	{
		enemy->initWithFile("enemy_rat2.png");
		enemy = static_cast<EnemyRatTwo *>(enemy->activateSettings(xPos, yPos));
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

Enemy* EnemyRatTwo::activateSettings(float xPos, float yPos)
{
	//Enemyクラスの、initEnemy(),initStatus(),setIdleAction()を呼び出し、
	//敵NPCの設定をする
	this->initStatus(kTag_rat1, RAT_TWO_HP, RAT_TWO_MAXHP, RAT_TWO_ATK);
	this->initEnemy(xPos, yPos);
	this->setIdleAction(-0.2, 0.2);
	return this;
}