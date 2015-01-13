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

void TitleState::s_titleToNormal() {
	Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

TitleState::TitleState()
	:_timer(0)
{
	_main = Main::getInstance();
	_om = Om::getInstance();
	_cm = Cm::getInstance();
}

TitleState::~TitleState() {

}

bool TitleState::onStateEnter() {
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *background = CCSprite::create("title_background.png");
	background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	_om->addChild(background, z_background, kTag_background);
	
	onNormal();

	return true;
}

void TitleState::stateUpdate(float dt) {

}

bool TitleState::onTouchBeganEvent(){
	return true;
}

void TitleState::onTouchMovedEvent(){

}

void TitleState::onTouchEndedEvent(){

}

bool TitleState::onStateExit() {
	CCLOG("TitleToNormal");
	_om->removeChildByTag(kTag_background);
	_om->removeChildByTag(kTag_retry);
	_om->playStart();
	return true;
}


void TitleState::onNormal(){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//���g���C�{�^��
	CCMenuItemImage *playButton = CCMenuItemImage::create("title_button_normal.png",
		"title_button_selected.png", this, menu_selector(TitleState::play));


	//�{�^�����烁�j���[���쐬����
	CCMenu *menu = CCMenu::create(playButton, NULL);

	//��ʂ̐^�񒆂֕\��
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_om->addChild(menu, z_retry, kTag_retry);
}

//�{�^���������ANormalState�֑J�ڂ���R�[���o�b�N�֐�
void TitleState::play(CCObject *pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_fire07.mp3");
	s_titleToNormal();
}
