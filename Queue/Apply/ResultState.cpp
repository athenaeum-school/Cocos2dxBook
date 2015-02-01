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

USING_NS_CC;

//状態のID
const std::string ResultState::s_resultID = "RESULT";

ResultState::ResultState():
m_timer(0)
{}

ResultState::~ResultState(){}

void ResultState::resultToNormal()
{
	//ObjectManagerのインスタンスを呼び出し、プレイヤーのターンへ遷移させる
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

void ResultState::resultToTitle() 
{
	//タイトル画面へ
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
	//AudioQueueに音源を追加
	OM::getInstance()->getAudioQueue()->enqueue("se_maoudamashii_system28.mp3");
	return true;
}

bool ResultState::onStateExit()
{
	//HudLayerのインスタンスを呼び出し、ボタンを削除
	Hud::getInstance()->removeChildByTag(kTag_retry);
	//ゲームオブジェクトのonStateExit()を実行
	this->objectStateExit();
	OM::getInstance()->setIsReady(false);
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
	menu->runAction(CCFadeIn::create(2));
}

//ボタン押下時、NormalStateへ遷移するコールバック関数
void ResultState::retry(CCObject *pSender){
	//効果音を再生
	OM::getInstance()->getAudioQueue()->playAudio("se_maoudamashii_system28.mp3");
	resultToNormal();
}

//ボタン押下時、TitleStateへ遷移するコールバック関数
void ResultState::back(CCObject *pSender){
	//効果音を再生
	OM::getInstance()->getAudioQueue()->playAudio("se_maoudamashii_system28.mp3");
	//BGMを停止
	OM::getInstance()->getAudioQueue()->stopAudio();
	resultToTitle();
}
