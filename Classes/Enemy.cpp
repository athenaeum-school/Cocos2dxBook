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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Enemy::Enemy(MainScene *main, int hp) 
: GameObject(main, hp)
, _isAttacked(false)
, _isContacted(false)
, _isDead(false)
{
	
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create(const char* fileName, int hp, float xPos, float yPos){
	//エネミー生成
	Enemy * enemy = new Enemy(Main::getInstance(), hp);
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
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 1 * this->radius()));
	this->setOpacity(0);

	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - 10 * this->radius())), NULL);

	CCSequence *seq = CCSequence::create(CCMoveBy::create(2, ccp(0, -this->radius() * 0.2)), CCMoveBy::create(2, ccp(0, this->radius() * 0.2)), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(seq);
	this->runAction(fadeIn);
	this->runAction(repeat);

	Om::getInstance()->initRaidHp(this->getHP());
	Om::getInstance()->addGameObjectMap("enemy", this);
	Om::getInstance()->addGameObject(this);
	
	return this;
}


void Enemy::stateUpdate(float dt){
	attack();
	hitCheck();

}



void Enemy::attack(){
	if (isDeadOrAttacked() || !isEnemyState()){
		return;
	}
		CCLOG("ATTACKING");
		setIsAttacked(true);
}

bool Enemy::isDeadOrAttacked(){
	if (_isDead || _isAttacked){
		return true;
	}
	return false;
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
	if (isContact && !_isContacted && !_isDead){
		CCLOG("enemyHit");
		damage();
		damageEffect();
		_isContacted = true;
	}
	else if (!isContact){
		_isContacted = false;
	}

}

void Enemy::damage(){
	Player *wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	int playerAtk = wisp->getAtk();
	_hp -= playerAtk;
	Om::getInstance()->damageRaidHp(playerAtk);
	CCLOG("hp : %d", _hp);

	if (_hp <= 0){
		setIsDead(true);
		setHP(0);
		died();
	}
}

void Enemy::died(){
	if (_isDead){
		diedEffect();
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_explosion04.mp3");
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
}

void Enemy::diedEffect(){
	//敵NPCを蒸発
	CCSpawn *diedSpawn = CCSpawn::create(CCScaleTo::create(1, 0, 1), CCFadeOut::create(1), nullptr);
	CCSequence *diedSequence = CCSequence::create(diedSpawn, nullptr);
	
	this->runAction(diedSequence);
	this->runAction(CCMoveBy::create(1, ccp(0, 20)));

	//消滅エフェクト
	CCSprite *vanish = CCSprite::create("dying1.png");
	vanish->setPosition(this->getPosition());
	_main->addChild(vanish, z_vanish);

	CCAnimation *vanishing = CCAnimation::create();
	vanishing->addSpriteFrameWithFileName("dying1.png");
	vanishing->addSpriteFrameWithFileName("dying2.png");
	vanishing->addSpriteFrameWithFileName("dying3.png");
	vanishing->addSpriteFrameWithFileName("dying4.png");
	vanishing->addSpriteFrameWithFileName("dying5.png");
	vanishing->setDelayPerUnit(0.2);

	CCSpawn *vanishSpawn = CCSpawn::create(CCAnimate::create(vanishing), CCFadeOut::create(1.0), nullptr);
	CCSequence *vanishSequence = CCSequence::create(vanishSpawn, CCRemoveSelf::create(), nullptr);

	vanish->runAction(vanishSequence);

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