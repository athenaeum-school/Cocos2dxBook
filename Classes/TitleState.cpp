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
//��Ԃ�ID
const std::string TitleState::s_titleID = "TITLE";

TitleState::TitleState()
:_timer(0)
{}

TitleState::~TitleState() {}


void TitleState::titleToNormal()
{
	Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

bool TitleState::onStateEnter() 
{
	//NormalState�ւ̃{�^����ǉ�
	onNormal();
	return true;
}

bool TitleState::onStateExit()
{
	CCLOG("TitleToNormal");
	_hud->removeChildByTag(kTag_background);
	_hud->removeChildByTag(kTag_retry);
	_om->playStart();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
	return true;
}

void TitleState::stateUpdate(float dt) {}

bool TitleState::onTouchBeganEvent()
{
	return true;
}

void TitleState::onTouchMovedEvent(){}

void TitleState::onTouchEndedEvent(){}

void TitleState::onNormal()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//�w�i�摜�̐ݒ�
	initBackground(screenSize);
	//�X�^�[�g�{�^��
	CCMenuItemImage *playButton = CCMenuItemImage::create("title_button_normal.png",
		"title_button_selected.png", this, menu_selector(TitleState::play));
	//�{�^�����烁�j���[���쐬����
	CCMenu *menu = CCMenu::create(playButton, NULL);
	//��ʂ̒����֕\��
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_hud->addChild(menu, z_retry, kTag_retry);
}

void TitleState::initBackground(CCSize screenSize)
{
	//�w�i�摜�̐ݒ�
	CCSprite *background = CCSprite::create("title_background.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_hud->addChild(background, z_background, kTag_background);
}

//�{�^���������ANormalState�֑J�ڂ���R�[���o�b�N�֐�
void TitleState::play(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_fire07.mp3");
	titleToNormal();
}
