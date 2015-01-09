/*
* Enemy.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "Enemy.h"
#include "MainScene.h"

USING_NS_CC;

Enemy::Enemy(MainScene *main)
:GameObject(main)
{
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create(const char* fileName, float xPos, float yPos){
	//エネミー生成
	Enemy * enemy = new Enemy(Main::getInstance());
	if (enemy) {
		enemy->initEnemy(fileName, xPos, yPos);
		enemy->autorelease();
		Main::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(const char* fileName, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile(fileName);
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 2 * this->radius()));
	
	//Game::getInstance()->addGameObjectMap("wisp", this);
	//Game::getInstance()->addGameObject(this);
	return this;
}

void Enemy::stateUpdate(float dt){

}
