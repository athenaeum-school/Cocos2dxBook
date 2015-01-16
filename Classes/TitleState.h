/*
* TitleState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__TitleState__
#define __WillYard__TitleState__


#include "GameState.h"
#include <cocos2d.h>
#include "MainScene.h"


class TitleState : public GameState
{
public:

	virtual void stateUpdate(float dt);
	virtual bool onStateEnter();
	virtual bool onStateExit();
	virtual bool onTouchBeganEvent();
	virtual void onTouchMovedEvent();
	virtual void onTouchEndedEvent();

	virtual std::string getStateID() { return s_titleID; }
	
	TitleState();
	~TitleState();

private:

	int _timer;

	static const std::string s_titleID;
	static void s_titleToNormal();

	void initBackground(cocos2d::CCSize screenSize);
	void play(cocos2d::CCObject *pSender);
	void onNormal();
	
};

#endif /* defined(__WillYard__TitleState__) */
