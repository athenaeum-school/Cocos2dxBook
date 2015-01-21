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
	//ゲームオブジェクトのコンテナをメンバーヘ代入
	_gObjects = _om->getGameObjects();
}

void GameState::objectStateEnter()
{
	//ゲームオブジェクトの状態開始処理を実行
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->onStateEnter();
	}
}

void GameState::objectStateExit()
{
	//ゲームオブジェクトの状態終了処理を実行
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->onStateExit();
	}
}

void GameState::objectStateUpdate(float dt)
{
	//ゲームオブジェクトの状態更新処理を実行
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		(*it)->stateUpdate(dt);
	}
}