/*
* HudLayer.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "HudLayer.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
//�V���O���g���̏�����
HudLayer* HudLayer::s_pInstance = 0;
//�_���[�W���x���̍���
const float HUD_POS = 20;
//���x���̃}�[�W��
const float MARGIN = 50;

HudLayer::HudLayer() :
m_hitCount(NULL),
m_pLabel(NULL),
m_pHitCountLabel(NULL),
m_pPlayerHpLabel(NULL)
{
	m_pAction = ActionManager::create();
}


HudLayer::~HudLayer()
{
	CC_SAFE_RELEASE_NULL(m_pPlayerHpLabel);
	CC_SAFE_RELEASE_NULL(m_pLabel);
	CC_SAFE_RELEASE_NULL(m_pHitCountLabel);
	CC_SAFE_RELEASE_NULL(m_pAction);
}

bool HudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	CCSize screennSize = CCDirector::sharedDirector()->getWinSize();
	//�E�B�X�v��HP���x����ǉ�
	m_pPlayerHpLabel = new CCLabelTTF();
	m_pPlayerHpLabel->initWithString("HP : 0", "arial", 18);
	m_pPlayerHpLabel->setColor(ccc3(127, 255, 212));
	m_pPlayerHpLabel->setPosition(ccp(screennSize.width / 4, screennSize.height / 1.2 + MARGIN));
	m_pPlayerHpLabel->setVisible(false);
	//�R���{�J�E���g���x����ǉ�
	m_pHitCountLabel = new CCLabelTTF();
	m_pHitCountLabel->initWithString("0", "arial", 30.0);
	m_pHitCountLabel->setColor(ccc3(255, 215, 0));
	m_pHitCountLabel->setPosition(ccp(screennSize.width - (m_pHitCountLabel->getContentSize().width) - MARGIN, screennSize.height / 1.5 + MARGIN));
	m_pHitCountLabel->setVisible(false);
	
	this->addChild(m_pPlayerHpLabel);
	this->addChild(m_pHitCountLabel);
	
	return true;
}


void HudLayer::damageLabel(CCPoint hudPos, int damage)
{
	//�_���[�W���x����ǉ�
	CCString *label = new CCString();
	CCLabelTTF *damageLabel = new CCLabelTTF();
	label->initWithFormat("%d", damage);
	damageLabel->initWithString("0", "arial", 25.0);
	damageLabel->setColor(ccc3(255, 165, 0));
	damageLabel->setPosition(ccp(hudPos.x, hudPos.y + HUD_POS));
	damageLabel->setString(label->getCString());
	this->addChild(damageLabel);
	CCSpawn *color = CCSpawn::create(CCTintTo::create(0.5, 255, 215, 0), CCFadeOut::create(0.5), NULL);
	//�J���[�ύX�A�N�V������A�폜����A�N�V����
	CCSequence *seq = CCSequence::create(color, CCRemoveSelf::create(), NULL);
	damageLabel->runAction(seq);
}

void HudLayer::addHitCountLabel()
{
	//�R���{���x����\��
	m_hitCount++;
	CCString *label = new CCString();
	label->initWithFormat("%d Hits", m_hitCount);
	m_pHitCountLabel->setString(label->getCString());
	m_pHitCountLabel->setVisible(true);
	//�q�b�g���閈�Ƀ��x�����Z���Ȃ�A�N�V����
	m_pHitCountLabel->runAction(CCTintBy::create(0.0, 0, -5, 10));
}

void HudLayer::hideHitCountLabel()
{
	//���x�����\���ɂ��A�F�����ɖ߂�
	m_pHitCountLabel->setVisible(false);
	m_pHitCountLabel->setColor(ccc3(255, 215, 0));
}

void HudLayer::drawHpLabel()
{
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//HP���x����\�����A�X�V���Ă���
	setHpLabelVisible(true);
	CCString *label = new CCString();
	label->initWithFormat("HP : %d", wisp->getHP());
	m_pPlayerHpLabel->setString(label->getCString());
}

void HudLayer::setHpLabelVisible(bool flg)
{
	//HP���x�����\����
	m_pPlayerHpLabel->setVisible(flg);
}

void HudLayer::initHpBar(GameObject *obj)
{
	//ObjectManager�̃C���X�^���X���Ăяo��
	//�E�B�X�v�̂݁A���U���g��Ԃ�HP�o�[���ő�ɖ߂�
	if (OM::getInstance()->getStateMachine()->getStates().back()->getStateID() == "RESULT")
	{
		CCProgressFromTo *add = CCProgressFromTo::create(0, obj->getHP(), obj->getMaxHP());
		obj->getHpBar()->runAction(add);
		return;
	} 
	//HP�o�[�̔w�i��ǉ�
	CCSprite *hpBgBar = CCSprite::create("hpBarBg.png");
	hpBgBar->setPosition(ccp(obj->getContentSize().width / 2, obj->getContentSize().height / 10 - 10));
	obj->addChild(hpBgBar, z_hpBarBg, kTag_hpbarBg);
	//HP�o�[��ǉ�
	obj->setHpBar(CCProgressTimer::create(CCSprite::create("hpBar.png")));
	CCProgressTimer *hpBar = obj->getHpBar();
	hpBar->setPosition(ccp(hpBgBar->getContentSize().width / 2, hpBgBar->getContentSize().height / 2));
	hpBar->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	hpBar->setMidpoint(ccp(0, 1));
	hpBar->setBarChangeRate(ccp(1, 0));
	hpBar->setPercentage(obj->getHpRatio());
	hpBgBar->addChild(hpBar, z_hpbar);
}

void HudLayer::drawHpBar(GameObject *obj)
{
	//HP�o�[�Ƀ_���[�W�𔽉f������
	CCProgressFromTo *draw = CCProgressFromTo::create(0.5, obj->getHP(), obj->getHpRatio());
	obj->getHpBar()->runAction(draw);
}

void HudLayer::readyImage()
{
	if (!OM::getInstance()->getIsReady())
	{
		return;
	}
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//Ready��ǉ�
	CCSprite *ready = CCSprite::create("normal_ready.png");
	ready->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	//�t�F�[�h�C�����邽�߁A������
	ready->setOpacity(0);
	this->addChild(ready);
	//�t�F�[�h�C�����A1�b���Fire���x����\�������AReady���x�����폜����A�N�V����
	CCSequence *readyFire = CCSequence::create(CCFadeIn::create(0.5), CCDelayTime::create(1.0), CCCallFunc::create(this, callfunc_selector(HudLayer::fireImage)), CCRemoveSelf::create(), NULL);
	ready->runAction(readyFire);
}

void HudLayer::fireImage()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//Fire���x����ǉ�
	CCSprite *fire = CCSprite::create("normal_fire.png");
	fire->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	this->addChild(fire);

	CCSpawn *scaleOut = CCSpawn::create(CCEaseIn::create(CCScaleTo::create(0.5, 2.0), 0.5), CCFadeOut::create(1), NULL);
	CCSequence *action = CCSequence::create(scaleOut, CCCallFunc::create(this, callfunc_selector(HudLayer::touchImage)),CCRemoveSelf::create(), NULL);
	fire->runAction(action);
	OM::getInstance()->setIsReady(false);
}

void HudLayer::aimImage()
{
	if (!OM::getInstance()->getIsReady())
	{
		//Aim���x����ǉ�
		CCSprite *aim = CCSprite::create("normalState_aim.png");
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		aim->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
		aim->setOpacity(0);
		this->addChild(aim);

		CCSequence *aimFade = CCSequence::create(
			CCFadeIn::create(0.5),
			CCFadeOut::create(0.5),
			CCCallFunc::create(this, callfunc_selector(HudLayer::touchImage)),
			CCRemoveSelf::create(),
			NULL);
		aim->runAction(aimFade);
	}
}

void HudLayer::touchImage()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//�^�b�`�C���[�W��ǉ�
	CCSprite * touchImage = CCSprite::create("normalState_touch.png");
	touchImage->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	this->addChild(touchImage, z_touch, ktag_touch);
	CCSequence *fade = CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(fade);
	touchImage->runAction(repeat);
}