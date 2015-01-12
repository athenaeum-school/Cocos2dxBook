/*
EnemyAttack* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyAttack.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

EnemyAttack::EnemyAttack()
	:_atk(0)
{

}


EnemyAttack::~EnemyAttack()
{
}

EnemyAttack* EnemyAttack::create(const char* fileName, CCPoint point){
	//エネミー生成
	EnemyAttack * enemyAttack = new EnemyAttack();
	if (enemyAttack) {
		enemyAttack->initEnemyAttack(fileName, point);
		enemyAttack->autorelease();
		Main::getInstance()->addChild(enemyAttack, z_enemyAttack, kTag_enemyAttack);
		return enemyAttack;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemyAttack);
	return NULL;
}

EnemyAttack* EnemyAttack::initEnemyAttack(const char* fileName, CCPoint point)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile(fileName);
	this->setPosition(point);
	
	return this;
}


void EnemyAttack::attack(Enemy *enemy){
	++_destroyTimer;
	setAtk(enemy->getAtk());
	CCLOG("getAtk%d", enemy->getAtk());
	MainScene *main = Main::getInstance();
	switch (enemy->getEtype())
	{
		{
			case enemyType::kTag_rat1:
			case enemyType::kTag_rat2:
				CCAnimation *attackEffect = CCAnimation::create();
				attackEffect->addSpriteFrameWithFileName("attack_rat1.png");
				attackEffect->addSpriteFrameWithFileName("attack_rat2.png");
				attackEffect->addSpriteFrameWithFileName("attack_rat3.png");
				attackEffect->setDelayPerUnit(0.1);

				CCAnimate *attackAnime = CCAnimate::create(attackEffect);

				Player *wisp = static_cast<Player *>(main->getChildByTag(kTag_wisp));
				CCMoveTo *attackMove = CCMoveTo::create(0.7f, ccp(wisp->getPositionX(), wisp->getPositionY()));
				CCSpawn *attackSpawn = CCSpawn::create(CCAnimate::create(attackEffect), attackMove, nullptr);

				this->runAction(attackSpawn);
				SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_wind02.mp3");
				break;
		}
		{
			case enemyType::kTag_vampire:
				CCAnimation *attackEffect = CCAnimation::create();
				attackEffect->addSpriteFrameWithFileName("attack_vampire1.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire2.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire3.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire4.png");
				attackEffect->setDelayPerUnit(0.2);

				CCAnimate *attackAnime = CCAnimate::create(attackEffect);

				Player *wisp = static_cast<Player *>(main->getChildByTag(kTag_wisp));
				CCMoveTo *attackMove = CCMoveTo::create(1.0f, ccp(wisp->getPositionX(), wisp->getPositionY()));
				CCSpawn *attackSpawn = CCSpawn::create(CCAnimate::create(attackEffect), attackMove,nullptr);

				this->runAction(attackSpawn);
				SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_magical23.mp3");
				break;
		}
		{
			default:
				break;
		}
	}
}

