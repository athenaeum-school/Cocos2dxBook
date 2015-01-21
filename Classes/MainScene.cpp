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
#include "HudLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
//シングルトンの初期化
MainScene* MainScene::s_pInstance = 0;

MainScene::MainScene(){}

MainScene:: ~MainScene()
{	
	_om->clean();
}

CCScene* MainScene::createScene()
{
    CCScene *scene = CCScene::create();
    MainScene *layer = MainScene::create();
	scene->addChild(layer);

	ObjectManager *om = ObjectManager::getInstance();
	om->init();
	scene->addChild(om);
	layer->_om = om;

	HudLayer *hud = HudLayer::getInstance();
	hud->init();
	scene->addChild(hud);
	layer->_hud = hud;

    return scene;
}

bool MainScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	MainScene::s_pInstance = this;

	//シングルタップモード
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	//ゲームをループさせる
	this->scheduleUpdate();

    return true;
}


void MainScene::update(float dt) {
	//状態マシーンのループ（ゲームのループ）
	_om->update(dt);
}


bool MainScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//入力をメンバーへ代入
	setBeganTouch(touch);
	return _om->handleBeganEvents();
}

void MainScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	//入力をメンバーへ代入
	setMovedTouch(touch);
	_om->handleMovedEvents();
}


void MainScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//入力をメンバーへ代入
	setEndedTouch(touch);
	_om->handleEndedEvents();
}
