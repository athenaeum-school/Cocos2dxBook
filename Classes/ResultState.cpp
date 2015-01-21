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
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
//��Ԃ�ID
const std::string ResultState::s_resultID = "RESULT";

ResultState::ResultState()
	:_timer(0)
{}

ResultState::~ResultState(){}

void ResultState::resultToNormal()
{
	Om::getInstance()->getStateMachine()->changeState(new NormalState());
}

void ResultState::resultToTitle() 
{
	Om::getInstance()->getStateMachine()->changeState(new TitleState());
}

bool ResultState::onStateEnter()
{
	CCLOG("Changed : resultState");
	//�v���C�J�E���g�𑝉�
	_om->addPlayCount();
	//_gObjects�ցA�R���e�i����
	setGameObjects();
	//�Q�[���I�u�W�F�N�g��onStateEnter()�����s
	objectStateEnter();
	//retry��back�{�^����\��
	onResult();

	return true;
}

bool ResultState::onStateExit()
{
	//�{�^�����폜
	_hud->removeChildByTag(kTag_retry);
	//�Q�[���I�u�W�F�N�g��onStateExit()�����s
	objectStateExit();
	_om->setIsReady(false);
	_om->setRaidHp(0);
	//�E�B�X�v��HP���x�����\����
	_hud->setLabelVisible(false);
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

	//���g���C�{�^��
	CCMenuItemImage *retryButton = CCMenuItemImage::create("result_button_retry_normal.png",
		"result_button_retry_selected.png", 
		this,
		menu_selector(ResultState::retry));
	//�o�b�N�{�^��
	CCMenuItemImage *backButton = CCMenuItemImage::create("result_button_back_normal.png",
		"result_button_back_selected.png", 
		this, 
		menu_selector(ResultState::back));

	//�{�^�����烁�j���[���쐬����
	CCMenu *menu = CCMenu::create(retryButton, backButton, NULL);
	
	//��ʂ̐^�񒆂֕\��
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	//�t�F�[�h�C�����邽�߁A������
	menu->setOpacity(0);
	_hud->addChild(menu, z_retry, kTag_retry);
	menu->runAction(CCFadeIn::create(2));
}

//�{�^���������ANormalState�֑J�ڂ���R�[���o�b�N�֐�
void ResultState::retry(CCObject *pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system28.mp3");
	resultToNormal();
}

//�{�^���������ATitleState�֑J�ڂ���R�[���o�b�N�֐�
void ResultState::back(CCObject *pSender){
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system28.mp3");
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	resultToTitle();
}
