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
const int RAT_ONE_ATKPOWER = 5;

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
		//MainSceneのインスタンスを呼び出し、そこに追加
		MS::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

std::string EnemyRatOne::initStatus(enemyType type)
{
	std::string fileName;
	//エネミータイプに応じて、ステータスを設定
	fileName = "enemy_rat1.png";
	this->setEnemyType(type);
	this->setHP(RAT_ONE_HP);
	this->setMaxHP(RAT_ONE_MAXHP);
	this->setAtkPower(RAT_ONE_ATKPOWER);
	
	return fileName;
}

void EnemyRatOne::setIdleAction()
{
	//HudLayerのインスタンスを呼び出す
	//待機アクション
	Hud::getInstance()->getAction()->enemyIdleAction(this, -0.2, 0.2);
}