/*
* GameObject.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(MainScene* main)
	: _vector(ccp(0, 0))
	, _nextPosition(ccp(0, 0))
{
	set_Main(main);
}

GameObject::~GameObject(){}

//void GameObject::damage(){}

float GameObject::radius(){
	if (_hp == 0){
		return 0.0;
	}

	return getTexture()->getContentSize().width * 0.5f;
}

void GameObject::setPosition(const CCPoint& pos){
	CCSprite::setPosition(pos);
	if (!_nextPosition.equals(pos)) {
		_nextPosition = pos;
	}
}