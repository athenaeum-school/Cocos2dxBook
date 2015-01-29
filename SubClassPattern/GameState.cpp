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
	//ObjectManagerのインスタンスを呼び出し、
	//ゲームオブジェクトのコンテナをメンバーヘ代入
	m_gameObjects = OM::getInstance()->getGameObjects();
}

void GameState::objectStateEnter()
{
	//ゲームオブジェクトの状態開始処理を実行
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		(*it)->onStateEnter();
	}
}

void GameState::objectStateExit()
{
	//ゲームオブジェクトの状態終了処理を実行
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		(*it)->onStateExit();
	}
}

void GameState::objectStateUpdate(float dt)
{
	//ゲームオブジェクトの状態更新処理を実行
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		(*it)->stateUpdate(dt);
	}
}