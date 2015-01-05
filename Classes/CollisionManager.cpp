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
{
	_main = Main::getInstance();
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

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);

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

void CollisionManager::addForceToWisp(){
	_main->cSetwispNextPositionX(_main->cGetWispVectorX());
	_main->cSetwispNextPositionY(_main->cGetWispVectorY());
}

void CollisionManager::addForceToWispX(float nextPos, float vector){
	_main->cSetwispNextPositionX(vector);
	//ObjectSprite* will = static_cast<ObjectSprite *>(_main->getWispTag());
	//will->setVector(ccp(nextPos, vector));
}

void CollisionManager::addForceToWispY(float nextPos, float vector){
	_main->cSetwispNextPositionY(vector);
}
