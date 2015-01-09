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

GameObject::GameObject(MainScene* main){
	set_Main(main);
}

GameObject::~GameObject(){}

float GameObject::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}

void GameObject::setPosition(const CCPoint& pos){
	CCSprite::setPosition(pos);
	if (!_nextPosition.equals(pos)) {
		_nextPosition = pos;
	}
}