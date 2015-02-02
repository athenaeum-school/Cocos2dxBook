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
#include "TitleState.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;
//状態のID
const std::string ResultState::s_resultID = "RESULT";

ResultState::ResultState():
m_timer(0)
{
	m_pAudio = new AudioComponent();
}

ResultState::~ResultState()
{
	delete m_pAudio;
	m_pAudio = NULL;
}

void ResultState::resultToNormal()
{
	//ObjectManagerのインスタンスを呼び出し、プレイヤーのターンへ遷移させる
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

void ResultState::resultToTitle() 
{
	OM::getInstance()->getStateMachine()->changeState(new TitleState());
}

bool ResultState::onStateEnter()
{
	//プレイ回数を増加
	OM::getInstance()->addPlayCount();
	//メンバーへゲームオブジェクトコンテナを代入
	this->setGameObjects();
	//ゲームオブジェクトのonStateEnter()を実行
	this->objectStateEnter();
	//retryとbackボタンを表示
	onResult();

	return true;
}

bool ResultState::onStateExit()
{
	//HudLayerのインスタンスを呼び出し、ボタンを削除
	Hud::getInstance()->removeChildByTag(kTag_retry);
	//ゲームオブジェクトのonStateExit()を実行
	this->objectStateExit();
	//ゲーム開始時のReadyを再度表示させるためのフラグを真に
	OM::getInstance()->setIsReady(true);
	OM::getInstance()->setRaidHp(0);
	//プレイヤーのHPラベルを非表示に
	Hud::getInstance()->setHpLabelVisible(false);
	return true;
}

void ResultState::stateUpdate(float dt) {}

bool ResultState::onTouchBeganEvent()
{
	return false;
}

void ResultState::onTouchMovedEvent(){}

void ResultState::onTouchEndedEvent(){}

void ResultState::onResult()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//リトライボタン
	CCMenuItemImage *retryButton =
		CCMenuItemImage::create(
		"result_button_retry_normal.png",
		"result_button_retry_selected.png",
		this,
		menu_selector(ResultState::retry));

	//バックボタン
	CCMenuItemImage *backButton =
		CCMenuItemImage::create(
		"result_button_back_normal.png",
		"result_button_back_selected.png",
		this,
		menu_selector(ResultState::back));

	//ボタンからメニューを作成する
	CCMenu *menu = CCMenu::create(retryButton, backButton, NULL);
	
	//画面の中央へ表示
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	//フェードインするため、透明に
	menu->setOpacity(0);
	Hud::getInstance()->addChild(menu, z_retry, kTag_retry);
	//2秒かけてフェードインするアクション
	menu->runAction(CCFadeIn::create(2));
}

//ボタン押下時、NormalStateへ遷移するコールバック関数
void ResultState::retry(CCObject *pSender)
{
	//AudioComponentから効果音を呼び出す
	m_pAudio->pushButtonSE();
	resultToNormal();
}

//ボタン押下時、TitleStateへ遷移するコールバック関数
void ResultState::back(CCObject *pSender)
{
	//AudioComponentから効果音を呼び出す
	m_pAudio->pushButtonSE();
	//BGMを停止
	m_pAudio->stopBackgroundMusic();
	resultToTitle();
}
