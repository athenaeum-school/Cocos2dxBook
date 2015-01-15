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
	, _label(NULL)
	, _comboLabel(NULL)
	, _comboCount(NULL)
	, _hp_label_wisp(NULL)
{
	_anime = AnimationManager::create();
}


HudLayer::~HudLayer()
{
	delete s_pInstance;
	s_pInstance = NULL;

	CC_SAFE_RELEASE_NULL(_hp_label_wisp);
	CC_SAFE_RELEASE_NULL(_label);
	CC_SAFE_RELEASE_NULL(_comboLabel);
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

	_hp_label_wisp = new CCLabelTTF();
	_hp_label_wisp->initWithString("HP : 0", "arial", 18);
	_hp_label_wisp->setColor(ccc3(127,255,212));
	
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


void HudLayer::update(float dt){
	
}


bool HudLayer::isLessThanDist(float dist, float radius){
	if (dist <= radius)
		return true;
	return false;
}

float HudLayer::CalcDiff(float nextPos, float getPos){
	float diff = nextPos - getPos;
	return diff;
}

float HudLayer::Calc(float powOne, float powTwo){
	float dist = powOne + powTwo;
	return dist;
}

void HudLayer::toString(int value)
{
	CCString *label = new CCString();
	label->initWithFormat("%d", value);
	_label->setString(label->getCString());
}

void HudLayer::damageToString(CCPoint hudPos, int damage){
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

void HudLayer::addComboCount(){
	_comboCount++;
	CCString *label = new CCString();
	label->initWithFormat("%d Hits", _comboCount);
	_comboLabel->setString(label->getCString());
	_comboLabel->setVisible(true);

	//CCSpawn *color = CCSpawn::create(CCTintBy::create(3.0, 255, 99, 71), NULL);
	CCSpawn *color = CCSpawn::create(CCTintBy::create(0.0, 0, -10, 10), NULL);
	CCSequence *seq = CCSequence::create(color, CCCallFunc::create(this, callfunc_selector(HudLayer::hide)), NULL);
	_comboLabel->runAction(seq);
}

void HudLayer::hide(){
	if (_comboCount >= 1){
		return;
	}
	_comboLabel->setVisible(false);
	_comboLabel->setColor(ccc3(255, 215, 0));
}

void HudLayer::drawMyHpLabel(){
	Player *wisp = static_cast<Player *>(Main::getInstance()->getChildByTag(kTag_wisp));
	setLabelVisible(true);
	CCString *label = new CCString();
	label->initWithFormat("HP : %d", wisp->getHP());
	_hp_label_wisp->setString(label->getCString());
	
}

void HudLayer::setLabelVisible(bool flg){ _hp_label_wisp->setVisible(flg); }