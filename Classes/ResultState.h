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

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;

	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

	std::string getStateID() override { return s_resultID; }
	
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
