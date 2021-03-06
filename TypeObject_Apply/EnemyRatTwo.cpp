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
const int RAT_TWO_ATKPOWER = 10;

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
		//MainSceneのインスタンスを呼び出し、そこに追加
		MS::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

std::string EnemyRatTwo::initStatus(enemyType type)
{
	std::string fileName;
	//エネミータイプに応じて、ステータスを設定
	fileName = "enemy_rat2.png";
	this->setEnemyType(type);
	this->setHP(RAT_TWO_HP);
	this->setMaxHP(RAT_TWO_MAXHP);
	this->setAtkPower(RAT_TWO_ATKPOWER);

	return fileName;
}

void EnemyRatTwo::setIdleAction()
{
	//HudLayerのインスタンスを呼び出す
	//待機アクション
	Hud::getInstance()->getAction()->enemyIdleAction(this, -0.2, 0.2);
}