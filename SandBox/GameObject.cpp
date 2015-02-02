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
	m_isPlayHitSE(false),
	m_isPlayHitFastSE(false),
	m_isPlayHitBlockSE(false),
	m_isPlayDyingSE(false),
	m_nextPosition(ccp(0, 0)),
	m_acceleration(ccp(0, 0)),
	m_pHpBar(NULL),
	m_pAudio(NULL)
{
	m_pAudio = new AudioComponent();
}

GameObject::~GameObject()
{
	CC_SAFE_RELEASE_NULL(m_pHpBar);
	delete m_pAudio;
	m_pAudio = NULL;
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

float GameObject::getRadius()
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

void GameObject::removeHpBar()
{
	if (m_pHpBar && this->getChildByTag(kTag_hpbarBg))
	{
		//hpBarBgから消去
		m_pHpBar->removeFromParent();
		//hpBar_bgはこのクラスに追加しているため、removeChildByTag()で消去
		this->removeChildByTag(kTag_hpbarBg);
	}
}