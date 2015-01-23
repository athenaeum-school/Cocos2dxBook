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

class TitleState : public GameState
{
public:

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

	std::string getStateID() override { return s_titleID; }
	
	TitleState();
	~TitleState();

private:

	int m_timer;
	static const std::string s_titleID;
	
	void titleToNormal();
	void onNormal();
	void initBackground(cocos2d::CCSize screenSize);
	void play(cocos2d::CCObject *pSender);

};

#endif /* defined(__WillYard__TitleState__) */
