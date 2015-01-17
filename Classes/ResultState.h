/*
* ResultState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ResultState__
#define __WillYard__ResultState__


#include "GameState.h"
#include <cocos2d.h>
#include "MainScene.h"


class ResultState : public GameState
{
public:

	virtual void stateUpdate(float dt);
	virtual bool onStateEnter();
	virtual bool onStateExit();
	virtual bool onTouchBeganEvent();
	virtual void onTouchMovedEvent();
	virtual void onTouchEndedEvent();
	
	virtual std::string getStateID() { return s_resultID; }
	
	ResultState();
	~ResultState();

private:

	int _timer;
	static const std::string s_resultID;

	void resultToNormal();
	void resultToTitle();

	void onResult();
	void retry(cocos2d::CCObject* pSender);
	void back(cocos2d::CCObject* pSender);
	
};

#endif /* defined(__WillYard__ResultState__) */
