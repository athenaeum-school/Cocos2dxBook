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

using namespace cocos2d;

class MainScene;
class ObjectManager;
class HudLayer;

class GameState : public CCSprite
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

	MainScene* _main;
	ObjectManager* _om;
	HudLayer* _hud;
	std::vector<GameObject*> _gObjects;

	void setGameObjects();
	void objectStateEnter();
	void objectStateExit();
	void objectStateUpdate(float dt);

private:
    
    bool m_loadingComplete;
    bool m_exiting;
	
};

#endif /* defined(__WillYard__GameState__) */
