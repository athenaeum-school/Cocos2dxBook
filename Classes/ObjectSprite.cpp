#include "ObjectSprite.h"

USING_NS_CC;

ObjectSprite::ObjectSprite()
{
}


ObjectSprite::~ObjectSprite()
{
}

ObjectSprite* ObjectSprite::create(const char * fileName){
	ObjectSprite * sprite = new ObjectSprite();
	if (sprite && sprite->initWithFile(fileName)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
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