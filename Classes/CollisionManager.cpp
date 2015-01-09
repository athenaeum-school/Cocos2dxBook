/*
* CollisionManager.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "CollisionManager.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


CollisionManager* CollisionManager::s_pInstance = 0;


CollisionManager::CollisionManager()
	:_main(Main::getInstance())
{
}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	SimpleAudioEngine *audio = SimpleAudioEngine::sharedEngine();
	audio->preloadEffect("se_maoudamashii_system48.mp3");
	audio->preloadEffect("se_maoudamashii_system45.mp3");
	audio->preloadBackgroundMusic("game_maoudamashii_7_rock46.mp3");
	audio->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
	
	return true;
}


void CollisionManager::update(float dt){
	
}


bool CollisionManager::isLessThanDist(float dist, float radius){
	if (dist <= radius)
		return true;
	return false;
}

float CollisionManager::CalcDiff(float nextPos, float getPos){
	float diff = nextPos - getPos;
	return diff;
}

float CollisionManager::Calc(float powOne, float powTwo){
	float dist = powOne + powTwo;
	return dist;
}


void CollisionManager::starEffect(){
	Player* wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//ダメージ時、スターエフェクト表示
	CCSprite *star = CCSprite::create("star1.png");
	star->setPosition(wisp->getPosition());
	addChild(star, z_star);

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

void CollisionManager::swingEffect(){
	Enemy *enemy = static_cast<Enemy *>(_main->getChildByTag(kTag_enemy));
	//ダメージ時、敵NPCをスイング
	CCRepeat *swing = CCRepeat::create(CCSequence::create(CCRotateTo::create(0.1, -10), CCRotateTo::create(0.1, 10), NULL), 4);
	enemy->runAction(CCSequence::create(swing, CCRotateTo::create(0, 0.125), NULL));
}

void CollisionManager::explodeEffect(){
	Enemy *enemy = static_cast<Enemy *>(_main->getChildByTag(kTag_enemy));
	//ダメージ時、爆発エフェクト表示
	CCSprite *ex = CCSprite::create("explode1.png");
	ex->setPosition(enemy->getPosition());
	addChild(ex, z_explode);

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

void CollisionManager::damageToEnemy(){
	CCLOG("damage");
	//ダメージ時、スターエフェクト表示
	starEffect();
	//ダメージ時、敵NPCをスイング
	swingEffect();
	//ダメージ時、爆発エフェクト表示
	explodeEffect();
}
