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
#include "ConcreteAudioComponent.h"

USING_NS_CC;

using namespace CocosDenshion;
//状態のID
const std::string TitleState::s_titleID = "TITLE";

TitleState::TitleState():
m_isPlayBGM(false),
m_timer(0),
m_pAudio(NULL)
{
	m_pAudio = new ConcreteAudioComponent();
}

TitleState::~TitleState() 
{
	delete m_pAudio;
	m_pAudio = NULL;
}


void TitleState::titleToNormal()
{
	//ObjectManagerのインスタンスを呼び出し、プレイヤーターンへ遷移
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

bool TitleState::onStateEnter() 
{
	//プレイヤーターンへのボタンを追加
	onNormal();
	return true;
}

bool TitleState::onStateExit()
{
	//タイトル画面の背景とスタートボタンを削除
	Hud::getInstance()->removeChildByTag(kTag_background);
	Hud::getInstance()->removeChildByTag(ktag_touch);
	//プレイスタート時の処理
	OM::getInstance()->playStart();
	//BGMを再生
	setIsPlayBGM(true);
	m_pAudio->playAudio(this);
	return true;
}

void TitleState::stateUpdate(float dt){}

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
	CCMenuItemImage *playButton = CCMenuItemImage::create(
		"title_button_normal.png",
		"title_button_selected.png",
		this,
		menu_selector(TitleState::play));
	//ボタンからメニューを作成する
	CCMenu *menu = CCMenu::create(playButton, NULL);
	//画面の中央へ表示
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	//HudLayerのインスタンスを呼び出し、そこに追加
	Hud::getInstance()->addChild(menu, z_touch, ktag_touch);
}

void TitleState::initBackground(CCSize screenSize)
{
	//背景画像の設定
	CCSprite *background = CCSprite::create("title_background.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	Hud::getInstance()->addChild(background, z_background, kTag_background);
}

//ボタン押下時、プレイヤーターンへ遷移するコールバック関数
void TitleState::play(CCObject *pSender)
{
	m_pAudio->playAudio(this);
	titleToNormal();
}
