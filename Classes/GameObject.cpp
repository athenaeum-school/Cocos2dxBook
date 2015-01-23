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
	//���݂̏�Ԃ�ID����
	m_stateID = OM::getInstance()->getStateMachine()->getStates().back()->getStateID();
}

bool GameObject::isNormalState()
{
	//�v���C���[�^�[�����m�F
	if (m_stateID == "NORMAL")
	{
		return true;
	}
	return false;
}

bool GameObject::isEnemyState()
{
	//�GNPC�^�[�����m�F
	if (m_stateID == "ENEMY")
	{
		return true;
	}
	return false;
}

bool GameObject::isResultState()
{
	//���U���g��Ԃ��m�F
	if (m_stateID == "RESULT")
	{
		return true;
	}
	return false;
}

void GameObject::isDeadWithRet()
{
	//���S���Ă����甲����
	if (m_isDead)
	{
		return;
	}
}

float GameObject::radius()
{
	//�摜�T�C�Y�̔��a��Ԃ�
	return getTexture()->getContentSize().width * 0.5;
}

void GameObject::setPosition(const CCPoint& pos)
{
	CCSprite::setPosition(pos);
	//���̖ڕW���W��ݒ肷��
	if (!m_nextPosition.equals(pos)) 
	{
		m_nextPosition = pos;
	}
}

float GameObject::getHpRatio()
{
	//HP�o�[�̊���
	return m_hp * 100.0 / m_maxHp;
}