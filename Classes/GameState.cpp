/*
* GameState.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "GameState.h"
#include "MainScene.h"
#include "ObjectManager.h"

GameState::GameState(){}

GameState::~GameState() {}

void GameState::setGameObjects()
{
	//�Q�[���I�u�W�F�N�g�̃R���e�i�������o�[�w���
	m_gObjects = OM::getInstance()->getGameObjects();
}

void GameState::objectStateEnter()
{
	//�Q�[���I�u�W�F�N�g�̏�ԊJ�n���������s
	for (std::vector<GameObject*>::iterator it = m_gObjects.begin(); it != m_gObjects.end(); ++it)
	{
		(*it)->onStateEnter();
	}
}

void GameState::objectStateExit()
{
	//�Q�[���I�u�W�F�N�g�̏�ԏI�����������s
	for (std::vector<GameObject*>::iterator it = m_gObjects.begin(); it != m_gObjects.end(); ++it)
	{
		(*it)->onStateExit();
	}
}

void GameState::objectStateUpdate(float dt)
{
	//�Q�[���I�u�W�F�N�g�̏�ԍX�V���������s
	for (std::vector<GameObject*>::iterator it = m_gObjects.begin(); it != m_gObjects.end(); ++it)
	{
		(*it)->stateUpdate(dt);
	}
}