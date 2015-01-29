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

float GameObject::getRadius()
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

void GameObject::removeHpBar()
{
	if (m_pHpBar && this->getChildByTag(kTag_hpbarBg))
	{
		//hpBarBg�������
		m_pHpBar->removeFromParent();
		//hpBar_bg�͂��̃N���X�ɒǉ����Ă��邽�߁AremoveChildByTag()�ŏ���
		this->removeChildByTag(kTag_hpbarBg);
	}
}