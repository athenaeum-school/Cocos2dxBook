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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


HudLayer* HudLayer::s_pInstance = 0;

const float HUD_POS = 20;

HudLayer::HudLayer()
	:_main(Main::getInstance())
	, _om(Om::getInstance())
	, _label(NULL)
	, _comboLabel(NULL)
	, _comboCount(NULL)
	, _hp_label_wisp(NULL)
{
	_anime = AnimationManager::create();
}


HudLayer::~HudLayer()
{
	CC_SAFE_RELEASE_NULL(_hp_label_wisp);
	CC_SAFE_RELEASE_NULL(_label);
	CC_SAFE_RELEASE_NULL(_comboLabel);
	CC_SAFE_RELEASE_NULL(_anime);
}

bool HudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	CCLOG("HudInit");
	CCSize screennSize = CCDirector::sharedDirector()->getWinSize();
	int margin = 50;
	//�E�B�X�v��HP���x����ǉ�
	_hp_label_wisp = new CCLabelTTF();
	_hp_label_wisp->initWithString("HP : 0", "arial", 18);
	_hp_label_wisp->setColor(ccc3(127,255,212));
	//�R���{�J�E���g���x����ǉ�
	_comboLabel = new CCLabelTTF();
	_comboLabel->initWithString("0", "arial", 30.0);
	_comboLabel->setColor(ccc3(255, 215, 0));
	_comboLabel->setPosition(ccp(screennSize.width - (_comboLabel->getContentSize().width) - margin, screennSize.height / 1.5 + margin));
	_comboLabel->setVisible(false);
	
	this->addChild(_hp_label_wisp);
	this->addChild(_comboLabel);
	_hp_label_wisp->setPosition(ccp(screennSize.width / 4, screennSize.height / 1.2 + margin));
	_hp_label_wisp->setVisible(false);
	return true;
}


void HudLayer::damageToString(CCPoint hudPos, int damage)
{
	//�_���[�W���x����ǉ�
	CCString *label = new CCString();
	CCLabelTTF *damageLabel = new CCLabelTTF();
	damageLabel->initWithString("0", "arial", 25.0);
	damageLabel->setColor(ccc3(255, 165, 0));
	label->initWithFormat("%d", damage);
	this->addChild(damageLabel);
	damageLabel->setPosition(ccp(hudPos.x, hudPos.y + HUD_POS));
	damageLabel->setString(label->getCString());

	CCSpawn *color = CCSpawn::create(CCTintTo::create(0.5, 255, 215, 0), CCFadeOut::create(0.5), NULL);
	CCSequence *seq = CCSequence::create(color, CCRemoveSelf::create(), NULL);
	damageLabel->runAction(seq);
}

void HudLayer::addComboCount()
{
	//�R���{���x����\��
	_comboCount++;
	CCString *label = new CCString();
	label->initWithFormat("%d Hits", _comboCount);
	_comboLabel->setString(label->getCString());
	_comboLabel->setVisible(true);
	//�q�b�g���閈�Ƀ��x�����Z���Ȃ�A�N�V����
	_comboLabel->runAction(CCTintBy::create(0.0, 0, -5, 10));
}

void HudLayer::hide()
{
	if (_comboCount >= 1)
	{
		return;
	}
	//���x�����\���ɂ��A�F�����ɖ߂�
	_comboLabel->setVisible(false);
	_comboLabel->setColor(ccc3(255, 215, 0));
}

void HudLayer::drawMyHpLabel()
{
	Player *wisp = static_cast<Player *>(Main::getInstance()->getChildByTag(kTag_wisp));
	//HP���x����\�����A�X�V���Ă���
	setLabelVisible(true);
	CCString *label = new CCString();
	label->initWithFormat("HP : %d", wisp->getHP());
	_hp_label_wisp->setString(label->getCString());
	
}

void HudLayer::setLabelVisible(bool flg)
{
	_hp_label_wisp->setVisible(flg); 
}

void HudLayer::ready()
{
	if (_om->getIsReady())
	{
		return;
	}
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//Ready���x����ǉ�
	CCSprite *ready = CCSprite::create("normal_ready.png");
	ready->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	//�t�F�[�h�C�����邽�߁A������
	ready->setOpacity(0);
	this->addChild(ready);
	//�t�F�[�h�C�����A1�b���Fire���x����\�������AReady���x�����폜����A�N�V����
	CCSequence *readyFire = CCSequence::create(CCFadeIn::create(0.5), CCDelayTime::create(1.0), CCCallFunc::create(this, callfunc_selector(HudLayer::fire)), CCRemoveSelf::create(), NULL);
	ready->runAction(readyFire);
}

void HudLayer::fire()
{
	CCLOG("fire");
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//Fire���x����ǉ�
	CCSprite *fire = CCSprite::create("normal_fire.png");
	fire->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	this->addChild(fire);

	CCSpawn *scaleOut = CCSpawn::create(CCEaseIn::create(CCScaleTo::create(0.5, 2.0), 0.5), CCFadeOut::create(1), NULL);
	CCSequence *action = CCSequence::create(scaleOut, CCRemoveSelf::create(), NULL);
	fire->runAction(action);
	_om->setIsReady(true);
}

void HudLayer::aim()
{
	if (_om->getIsReady())
	{
		//Aim���x����ǉ�
		CCSprite *aim = CCSprite::create("normalState_aim.png");
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		aim->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
		aim->setOpacity(0);
		this->addChild(aim);

		CCSequence *aimFade = CCSequence::create(CCFadeIn::create(0.5), CCFadeOut::create(0.5), CCRemoveSelf::create(), NULL);
		aim->runAction(aimFade);
	}
}
