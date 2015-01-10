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
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const std::string ResultState::s_resultID = "RESULT";

void ResultState::s_resultToNormal() {
	CCLOG("NormalState : changed");
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

bool ResultState::onStateEnter() {
	CCLOG("Changed : resultState");
	onResult();
	return true;
}

bool ResultState::onStateExit() {
	CCLOG("ResultToNormal");
	_om->removeAllChildren();
	return true;
}

void ResultState::onResult(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//もう一度遊ぶボタン
	CCMenuItemImage *replayButton = CCMenuItemImage::create("retry_button.png",
		"retry_button.png", this, menu_selector(ResultState::retry));


	//２つのボタンからメニューを作成する
	CCMenu *menu = CCMenu::create(replayButton, NULL);
	//たてに並べる
	menu->setPosition(ccp(winSize.width / 2.0, winSize.height / 2.0));
	_om->addChild(menu, kTag_retry, z_retry);
}

void ResultState::retry(CCObject *pSender){
	s_resultToNormal();
}