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
	//���݂̏�Ԃ�ID����
	_stateID = _om->getStateMachine()->getStates().back()->getStateID();
}

bool GameObject::isNormalState()
{
	//�v���C���[�^�[�����m�F
	if (_stateID == "NORMAL")
	{
		return true;
	}
	return false;
}

bool GameObject::isEnemyState()
{
	//�GNPC�^�[�����m�F
	if (_stateID == "ENEMY")
	{
		return true;
	}
	return false;
}

bool GameObject::isResultState()
{
	//���U���g��Ԃ��m�F
	if (_stateID == "RESULT")
	{
		return true;
	}
	return false;
}

void GameObject::isDeadWithRet()
{
	//���S���Ă����甲����
	if (_isDead)
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
	if (!_nextPosition.equals(pos)) 
	{
		_nextPosition = pos;
	}
}

float GameObject::getHpRatio()
{
	//HP�o�[�̊���
	return _hp * 100.0 / _maxHp;
}