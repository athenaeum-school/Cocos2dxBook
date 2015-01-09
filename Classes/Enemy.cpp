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
, _isHit(false)
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
	
	Om::getInstance()->addGameObjectMap("enemy", this);
	Om::getInstance()->addGameObject(this);
	
	return this;
}

void Enemy::stateUpdate(float dt){
	attack();
	hitCheck();

}

void Enemy::attack(){
	if (isEnemyState())
	{
		CCLOG("ATTACKING");
	}
}

bool Enemy::isEnemyState(){
	if (Om::getInstance()->getStateMachine()->getStates().back()->getStateID() == "ENEMY")
	{
		return true;
	}

	return false;
}

void Enemy::hitCheck(){
	CCPoint enemyPosition = this->getPosition();
	Player *wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	CCRect wispRect = wisp->boundingBox();
	bool isContact = wispRect.containsPoint(enemyPosition);
	if (isContact && !_isHit){
		CCLOG("enemyHit");
		damageEffect();
		_isHit = true;
	}
	else if (!isContact){
		_isHit = false;
	}
}


void Enemy::damageEffect(){
	CCLOG("damage");
	//ダメージ時、スターエフェクト表示
	starEffect();
	//ダメージ時、敵NPCをスイング
	swingEffect();
	//ダメージ時、爆発エフェクト表示
	explodeEffect();
	//this->setVisible(false);
}

void Enemy::starEffect(){
	Player* wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//ダメージ時、スターエフェクト表示
	CCSprite *star = CCSprite::create("star1.png");
	star->setPosition(wisp->getPosition());
	_main->addChild(star, z_star);

	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("star1.png");
	animation->addSpriteFrameWithFileName("star2.png");
	animation->addSpriteFrameWithFileName("star3.png");
	animation->addSpriteFrameWithFileName("star4.png");
	animation->setDelayPerUnit(0.1);

	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), CCFadeOut::create(0.45), nullptr);
	CCSequence *starSequence = CCSequence::create(spawn, CCRemoveSelf::create(), nullptr);

	star->runAction(CCScaleTo::create(0.4, 2));
	star->runAction(starSequence);
}

void Enemy::swingEffect(){
	//ダメージ時、敵NPCをスイング
	CCRepeat *swing = CCRepeat::create(CCSequence::create(CCRotateTo::create(0.1, -10), CCRotateTo::create(0.1, 10), NULL), 4);
	this->runAction(CCSequence::create(swing, CCRotateTo::create(0, 0.125), NULL));
}



void Enemy::explodeEffect(){
	//ダメージ時、爆発エフェクト表示
	CCSprite *ex = CCSprite::create("explode1.png");
	ex->setPosition(this->getPosition());
	_main->addChild(ex, z_explode);

	CCAnimation *explode = CCAnimation::create();
	explode->addSpriteFrameWithFileName("explode1.png");
	explode->addSpriteFrameWithFileName("explode2.png");
	explode->addSpriteFrameWithFileName("explode3.png");
	explode->addSpriteFrameWithFileName("explode4.png");
	explode->setDelayPerUnit(0.1);

	CCSpawn *exSpawn = CCSpawn::create(CCAnimate::create(explode), CCFadeOut::create(0.45), nullptr);
	CCSequence *exSequence = CCSequence::create(exSpawn, CCRemoveSelf::create(), nullptr);

	ex->runAction(exSequence);

}