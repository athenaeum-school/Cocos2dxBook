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
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"
#include "AudioComponent.h"

USING_NS_CC;

using namespace CocosDenshion;
//状態のID
const std::string TitleState::s_titleID = "TITLE";

TitleState::TitleState() :
m_timer(0),
m_pAudio(NULL)
{}

TitleState::~TitleState() 
{
	delete m_pAudio;
	m_pAudio = NULL;
}


void TitleState::titleToNormal()
{
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

bool TitleState::onStateEnter() 
{
	//オーディオの初期化
	m_pAudio = new AudioComponent();
	//NormalStateへのボタンを追加
	onNormal();
	return true;
}

bool TitleState::onStateExit()
{
	CCLOG("TitleToNormal");
	Hud::getInstance()->removeChildByTag(kTag_background);
	Hud::getInstance()->removeChildByTag(kTag_retry);
	OM::getInstance()->playStart();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
	return true;
}

void TitleState::stateUpdate(float dt) 
{}

bool TitleState::onTouchBeganEvent()
{
	return true;
}

void TitleState::onTouchMovedEvent(){}

void TitleState::onTouchEndedEvent(){}

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
	Hud::getInstance()->addChild(menu, z_retry, kTag_retry);
}

void TitleState::initBackground(CCSize screenSize)
{
	//背景画像の設定
	CCSprite *background = CCSprite::create("title_background.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	Hud::getInstance()->addChild(background, z_background, kTag_background);
}

//ボタン押下時、NormalStateへ遷移するコールバック関数
void TitleState::play(CCObject *pSender)
{
	m_pAudio->titleToNormalSE();
	titleToNormal();
}
