/*
* GameObject.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__GameObject__
#define __WillYard__GameObject__

#include <iostream>
#include <cocos2d.h>


class MainScene;

class GameObject : public cocos2d::CCSprite
{
public:
   
	virtual void stateUpdate(float dt) = 0;
	
	CC_SYNTHESIZE(MainScene *, _main, _Main);
	CC_SYNTHESIZE(cocos2d::CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _vector, Vector);
	virtual void setPosition(const cocos2d::CCPoint& pos);
	virtual float radius();

	GameObject(MainScene* main);
	~GameObject();
};


#endif /* defined(__WillYard__GameObject__) */
