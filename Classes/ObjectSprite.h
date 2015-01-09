/*
* ObjectSprite.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ObjectSprite__
#define __WillYard__ObjectSprite__

#include "cocos2d.h"
#include "GameObject.h"

class MainScene;

class ObjectSprite : public GameObject {
private:
	ObjectSprite* initObject();

public:
	virtual void stateUpdate(float dt);

	CC_SYNTHESIZE(cocos2d::CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _vector, Vector);
	static ObjectSprite* create();
	static ObjectSprite* create(const char * fileName);
	virtual void setPosition(const cocos2d::CCPoint& pos);
	float radius();

	ObjectSprite(MainScene *main);
	~ObjectSprite(void);
};

#endif /*defined(__WillYard__ObjectSprite__)*/


