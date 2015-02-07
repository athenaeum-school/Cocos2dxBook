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
const int VAMPIRE_ATKPOWER = 20;

EnemyVampire::EnemyVampire(){}

EnemyVampire::~EnemyVampire(){}

EnemyVampire* EnemyVampire::create(enemyType type, float xPos, float yPos)
{
	//エネミー生成
	EnemyVampire * enemy = new EnemyVampire();
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

std::string EnemyVampire::initStatus(enemyType type)
{
	std::string fileName;
	//エネミータイプに応じて、ステータスを設定
	fileName = "enemy_vampire.png";
	this->setEnemyType(type);
	this->setHP(VAMPIRE_HP);
	this->setMaxHP(VAMPIRE_MAXHP);
	this->setAtkPower(VAMPIRE_ATKPOWER);
	
	return fileName;
}

void EnemyVampire::setIdleAction()
{
	//HudLayerのインスタンスを呼び出す
	//待機アクション
	Hud::getInstance()->getAction()->enemyIdleAction(this, 0.2, -0.2);
}