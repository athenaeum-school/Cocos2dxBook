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
#include "HudLayer.h"
#include "MainScene.h"

USING_NS_CC;

GameObject::GameObject()
	: _main(Main::getInstance())
	, _hud(Hud::getInstance())
	, _om(Om::getInstance())
	, _isDead(false)
	, _nextPosition(ccp(0, 0))
	, _vector(ccp(0, 0))
	, _hpBar(NULL)
{
}

GameObject::~GameObject()
{
	CC_SAFE_RELEASE_NULL(_hpBar);
}

void GameObject::setStateID()
{
	//現在の状態のIDを代入
	_stateID = _om->getStateMachine()->getStates().back()->getStateID();
}

bool GameObject::isNormalState()
{
	//プレイヤーターンか確認
	if (_stateID == "NORMAL")
	{
		return true;
	}
	return false;
}

bool GameObject::isEnemyState()
{
	//敵NPCターンか確認
	if (_stateID == "ENEMY")
	{
		return true;
	}
	return false;
}

bool GameObject::isResultState()
{
	//リザルト状態か確認
	if (_stateID == "RESULT")
	{
		return true;
	}
	return false;
}

void GameObject::isDeadWithRet()
{
	//死亡していたら抜ける
	if (_isDead)
	{
		return;
	}
}

float GameObject::radius()
{
	//画像サイズの半径を返す
	return getTexture()->getContentSize().width * 0.5;
}

void GameObject::setPosition(const CCPoint& pos)
{
	CCSprite::setPosition(pos);
	//次の目標座標を設定する
	if (!_nextPosition.equals(pos)) 
	{
		_nextPosition = pos;
	}
}

float GameObject::getHpRatio()
{
	//HPバーの割合
	return _hp * 100.0 / _maxHp;
}