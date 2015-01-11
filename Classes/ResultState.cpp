/*
* ResultState.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "ResultState.h"
#include "NormalState.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const std::string ResultState::s_resultID = "RESULT";

void ResultState::s_resultToNormal() {
	Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

void ResultState::s_resultToIdle() {
	//Game::Instance()->getStateMachine()->changeState(new IdleState());
}

ResultState::ResultState()
	:_timer(0)
{
	_main = Main::getInstance();
	_om = Om::getInstance();
	_cm = Cm::getInstance();
}

ResultState::~ResultState() {

}

bool ResultState::onStateEnter() {
	CCLOG("Changed : resultState");
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *back = CCSprite::create("HelloWorld.png");
	back->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	back->setOpacity(0);
	_om->addChild(back, z_background, kTag_background);
	back->runAction(CCFadeIn::create(2));

	onResult();

	return true;
}

void ResultState::stateUpdate(float dt) {

}

bool ResultState::onTouchBeganEvent(){
	CCLOG("TouchBegan");
	return true;
}

void ResultState::onTouchMovedEvent(){
	
}

void ResultState::onTouchEndedEvent(){
	
}

bool ResultState::onStateExit() {
	CCLOG("ResultToNormal");
	_om->removeChildByTag(kTag_background);
	_om->removeChildByTag(kTag_retry);
	return true;
}

void ResultState::onResult(){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//リトライボタン
	CCMenuItemImage *replayButton = CCMenuItemImage::create("retry_button.png",
		"retry_button.png", this, menu_selector(ResultState::retry));


	//ボタンからメニューを作成する
	CCMenu *menu = CCMenu::create(replayButton, NULL);
	
	//画面の真ん中へ表示
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	menu->setOpacity(0);
	_om->addChild(menu, z_retry, kTag_retry);
	menu->runAction(CCFadeIn::create(2));
}

//ボタン押下時、NormalStateへ遷移するコールバック関数
void ResultState::retry(CCObject *pSender){
	s_resultToNormal();
}