/*
* ObjectSprite.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "ObjectSprite.h"
#include "MainScene.h"

USING_NS_CC;

ObjectSprite::ObjectSprite(MainScene *main)
:GameObject(main)
{
}


ObjectSprite::~ObjectSprite()
{
}

ObjectSprite* ObjectSprite::create(){
	ObjectSprite * sprite = new ObjectSprite(Main::getInstance());
	//if (sprite && sprite->initWithFile(fileName)) {
	if (sprite){
		sprite->initObject();
		sprite->autorelease();
		Main::getInstance()->addChild(sprite);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

ObjectSprite* ObjectSprite::create(const char * fileName){
	ObjectSprite * sprite = new ObjectSprite(Main::getInstance());
	if (sprite && sprite->initWithFile(fileName)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

ObjectSprite* ObjectSprite::initObject()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile("wisp_1.png");
	this->setPosition(ccp(screenSize.width * 0.5, this->radius() * 2));
	this->setTag(1);
	this->setZOrder(z_wisp);

	//Game::getInstance()->addGameObjectMap("wisp", this);
	//Game::getInstance()->addGameObject(this);
	return this;
}

void ObjectSprite::stateUpdate(float dt){

}

void ObjectSprite::setPosition(const CCPoint& pos){
	CCSprite::setPosition(pos);
	if (!_nextPosition.equals(pos)) {
		_nextPosition = pos;
	}
}

float ObjectSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}