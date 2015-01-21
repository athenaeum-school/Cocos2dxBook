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

GameState::GameState()
	:_main(Main::getInstance())
	, _hud(Hud::getInstance())
	, _om(Om::getInstance())
{}

GameState::~GameState() {}

void GameState::setGameObjects()
{
	//�Q�[���I�u�W�F�N�g�̃R���e�i�������o�[�w���
	_gObjects = _om->getGameObjects();
}

void GameState::objectStateEnter()
{
	//�Q�[���I�u�W�F�N�g�̏�ԊJ�n���������s
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->onStateEnter();
	}
}

void GameState::objectStateExit()
{
	//�Q�[���I�u�W�F�N�g�̏�ԏI�����������s
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->onStateExit();
	}
}

void GameState::objectStateUpdate(float dt)
{
	//�Q�[���I�u�W�F�N�g�̏�ԍX�V���������s
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->stateUpdate(dt);
	}
}