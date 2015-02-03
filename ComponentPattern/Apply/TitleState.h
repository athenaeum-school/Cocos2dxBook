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
#include "AudioComponent.h"

class TitleState : public GameState
{
public:

	CC_SYNTHESIZE(bool, m_isPlayBGM, IsPlayBGM);

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
	AudioComponent *m_pAudio;
	
	void titleToNormal();

	//スタートボタンを表示
	void onNormal();

	/**	背景を追加
	*	@param screenSize 画面サイズ
	*/
	void initBackground(cocos2d::CCSize screenSize);

	/**	ボタン押下時、プレイヤーターンへ遷移するコールバック関数
	*	@param pSender menuSelectorの引数の引数の型
	*/
	void play(cocos2d::CCObject *pSender);

};

#endif /* defined(__WillYard__TitleState__) */
