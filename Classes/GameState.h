/*
* GameState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__GameState__
#define __WillYard__GameState__

#include "cocos2d.h"
#include "GameObject.h"

class GameState : public cocos2d::CCSprite
{
public:

	virtual void stateUpdate(float dt) = 0;
    virtual bool onStateEnter() = 0;
    virtual bool onStateExit() = 0;
    virtual bool onTouchBeganEvent() = 0;
	virtual void onTouchMovedEvent() = 0;
	virtual void onTouchEndedEvent() = 0;

    virtual std::string getStateID() = 0;

    GameState();
    ~GameState();
    
protected:

	std::vector<GameObject*> m_gameObjects;

	//ゲームオブジェクトのコンテナをm_gameObjectsヘ代入
	void setGameObjects();

	//ゲームオブジェクトの状態開始処理を実行
	void objectStateEnter();

	//ゲームオブジェクトの状態終了処理を実行
	void objectStateExit();

	//ゲームオブジェクトの状態更新処理を実行
	void objectStateUpdate(float dt);

};

#endif /* defined(__WillYard__GameState__) */
