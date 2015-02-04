/*
* MainScene.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
//シングルトンの初期化
MainScene* MainScene::s_pInstance = 0;

MainScene::MainScene(){}

MainScene:: ~MainScene()
{	
	OM::getInstance()->clean();
}

CCScene* MainScene::createScene()
{
    CCScene *scene = CCScene::create();
	MainScene *layer = MainScene::create();
	scene->addChild(layer);
	
	HudLayer *hud = HudLayer::getInstance();
	hud->init();
	scene->addChild(hud);
	
    return scene;
}

bool MainScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	MainScene::s_pInstance = this;

	OM::getInstance()->init();

	//シングルタップモード
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	//ゲームをループさせる
	this->scheduleUpdate();

    return true;
}


void MainScene::update(float dt) {
	//ObjectManagerのインスタンスを呼び出す
	//状態マシーンのループ（ゲームのループ）
	OM::getInstance()->update(dt);
}


bool MainScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//入力をメンバーへ代入
	setBeganTouch(touch);
	return OM::getInstance()->handleBeganEvents();
}

void MainScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	//入力をメンバーへ代入
	setMovedTouch(touch);
	OM::getInstance()->handleMovedEvents();
}


void MainScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//入力をメンバーへ代入
	setEndedTouch(touch);
	OM::getInstance()->handleEndedEvents();
}
