/*
* TitleState.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "TitleState.h"
#include "NormalState.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const std::string TitleState::s_titleID = "TITLE";

void TitleState::s_titleToNormal() 
{
	Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

TitleState::TitleState()
:_timer(0)
{
	
}

TitleState::~TitleState() {}

bool TitleState::onStateEnter() 
{
	onNormal();
	return true;
}

void TitleState::stateUpdate(float dt) {}

bool TitleState::onTouchBeganEvent()
{
	return true;
}

void TitleState::onTouchMovedEvent(){}

void TitleState::onTouchEndedEvent(){}

bool TitleState::onStateExit() 
{
	CCLOG("TitleToNormal");
	_hud->removeChildByTag(kTag_background);
	_hud->removeChildByTag(kTag_retry);
	_om->playStart();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
	return true;
}

//背景画像の設定
void TitleState::initBackground(CCSize screenSize)
{
	CCSprite *background = CCSprite::create("title_background.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_hud->addChild(background, z_background, kTag_background);
}

//NormalStateへのボタンの設定
void TitleState::onNormal()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//背景画像の設定
	initBackground(screenSize);
	//スタートボタン
	CCMenuItemImage *playButton = CCMenuItemImage::create("title_button_normal.png",
		"title_button_selected.png", this, menu_selector(TitleState::play));
	//ボタンからメニューを作成する
	CCMenu *menu = CCMenu::create(playButton, NULL);
	//画面の中央へ表示
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_hud->addChild(menu, z_retry, kTag_retry);
}

//ボタン押下時、NormalStateへ遷移するコールバック関数
void TitleState::play(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_fire07.mp3");
	s_titleToNormal();
}
