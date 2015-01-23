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
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"


USING_NS_CC;

GameObject::GameObject() : 
	m_isDead(false),
	m_nextPosition(ccp(0, 0)),
	m_vector(ccp(0, 0)),
	m_pHpBar(NULL)
{
}

GameObject::~GameObject()
{
	CC_SAFE_RELEASE_NULL(m_pHpBar);
}

void GameObject::setStateID()
{
	//現在の状態のIDを代入
	m_stateID = OM::getInstance()->getStateMachine()->getStates().back()->getStateID();
}

bool GameObject::isNormalState()
{
	//プレイヤーターンか確認
	if (m_stateID == "NORMAL")
	{
		return true;
	}
	return false;
}

bool GameObject::isEnemyState()
{
	//敵NPCターンか確認
	if (m_stateID == "ENEMY")
	{
		return true;
	}
	return false;
}

bool GameObject::isResultState()
{
	//リザルト状態か確認
	if (m_stateID == "RESULT")
	{
		return true;
	}
	return false;
}

void GameObject::isDeadWithRet()
{
	//死亡していたら抜ける
	if (m_isDead)
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
	if (!m_nextPosition.equals(pos)) 
	{
		m_nextPosition = pos;
	}
}

float GameObject::getHpRatio()
{
	//HPバーの割合
	return m_hp * 100.0 / m_maxHp;
}