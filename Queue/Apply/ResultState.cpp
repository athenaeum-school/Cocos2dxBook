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

//��Ԃ�ID
const std::string ResultState::s_resultID = "RESULT";

ResultState::ResultState():
m_timer(0)
{}

ResultState::~ResultState(){}

void ResultState::resultToNormal()
{
	//ObjectManager�̃C���X�^���X���Ăяo���A�v���C���[�̃^�[���֑J�ڂ�����
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

void ResultState::resultToTitle() 
{
	//�^�C�g����ʂ�
	OM::getInstance()->getStateMachine()->changeState(new TitleState());
}

bool ResultState::onStateEnter()
{
	//�v���C�񐔂𑝉�
	OM::getInstance()->addPlayCount();
	//�����o�[�փQ�[���I�u�W�F�N�g�R���e�i����
	this->setGameObjects();
	//�Q�[���I�u�W�F�N�g��onStateEnter()�����s
	this->objectStateEnter();
	//retry��back�{�^����\��
	onResult();
	//AudioQueue�ɉ�����ǉ�
	OM::getInstance()->getAudioQueue()->enqueue("se_maoudamashii_system28.mp3");
	return true;
}

bool ResultState::onStateExit()
{
	//HudLayer�̃C���X�^���X���Ăяo���A�{�^�����폜
	Hud::getInstance()->removeChildByTag(kTag_retry);
	//�Q�[���I�u�W�F�N�g��onStateExit()�����s
	this->objectStateExit();
	OM::getInstance()->setIsReady(false);
	OM::getInstance()->setRaidHp(0);
	//�v���C���[��HP���x�����\����
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

	//���g���C�{�^��
	CCMenuItemImage *retryButton =
		CCMenuItemImage::create(
		"result_button_retry_normal.png",
		"result_button_retry_selected.png",
		this,
		menu_selector(ResultState::retry));

	//�o�b�N�{�^��
	CCMenuItemImage *backButton =
		CCMenuItemImage::create(
		"result_button_back_normal.png",
		"result_button_back_selected.png",
		this,
		menu_selector(ResultState::back));

	//�{�^�����烁�j���[���쐬����
	CCMenu *menu = CCMenu::create(retryButton, backButton, NULL);
	
	//��ʂ̒����֕\��
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));

	//�t�F�[�h�C�����邽�߁A������
	menu->setOpacity(0);
	Hud::getInstance()->addChild(menu, z_retry, kTag_retry);
	menu->runAction(CCFadeIn::create(2));
}

//�{�^���������ANormalState�֑J�ڂ���R�[���o�b�N�֐�
void ResultState::retry(CCObject *pSender){
	//���ʉ����Đ�
	OM::getInstance()->getAudioQueue()->playAudio("se_maoudamashii_system28.mp3");
	resultToNormal();
}

//�{�^���������ATitleState�֑J�ڂ���R�[���o�b�N�֐�
void ResultState::back(CCObject *pSender){
	//���ʉ����Đ�
	OM::getInstance()->getAudioQueue()->playAudio("se_maoudamashii_system28.mp3");
	//BGM���~
	OM::getInstance()->getAudioQueue()->stopAudio();
	resultToTitle();
}