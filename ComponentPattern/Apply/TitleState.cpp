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
//��Ԃ�ID
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
	//ObjectManager�̃C���X�^���X���Ăяo���A�v���C���[�^�[���֑J��
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

bool TitleState::onStateEnter() 
{
	//�v���C���[�^�[���ւ̃{�^����ǉ�
	onNormal();
	return true;
}

bool TitleState::onStateExit()
{
	//�^�C�g����ʂ̔w�i�ƃX�^�[�g�{�^�����폜
	Hud::getInstance()->removeChildByTag(kTag_background);
	Hud::getInstance()->removeChildByTag(ktag_touch);
	//�v���C�X�^�[�g���̏���
	OM::getInstance()->playStart();
	//BGM���Đ�
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
	//�w�i�摜�̐ݒ�
	initBackground(screenSize);
	//�X�^�[�g�{�^��
	CCMenuItemImage *playButton = CCMenuItemImage::create(
		"title_button_normal.png",
		"title_button_selected.png",
		this,
		menu_selector(TitleState::play));
	//�{�^�����烁�j���[���쐬����
	CCMenu *menu = CCMenu::create(playButton, NULL);
	//��ʂ̒����֕\��
	menu->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	//HudLayer�̃C���X�^���X���Ăяo���A�����ɒǉ�
	Hud::getInstance()->addChild(menu, z_touch, ktag_touch);
}

void TitleState::initBackground(CCSize screenSize)
{
	//�w�i�摜�̐ݒ�
	CCSprite *background = CCSprite::create("title_background.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	Hud::getInstance()->addChild(background, z_background, kTag_background);
}

//�{�^���������A�v���C���[�^�[���֑J�ڂ���R�[���o�b�N�֐�
void TitleState::play(CCObject *pSender)
{
	m_pAudio->playAudio(this);
	titleToNormal();
}
