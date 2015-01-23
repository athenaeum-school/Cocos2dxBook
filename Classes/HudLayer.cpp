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
//シングルトンの初期化
HudLayer* HudLayer::s_pInstance = 0;
//ダメージラベルの高さ
const float HUD_POS = 20;
//ラベルのマージン
const float MARGIN = 50;

HudLayer::HudLayer() :
m_pLabel(NULL),
m_pComboLabel(NULL),
m_comboCount(NULL),
m_pPlayerHpLabel(NULL)
{
	m_pAnime = AnimationManager::create();
}


HudLayer::~HudLayer()
{
	CC_SAFE_RELEASE_NULL(m_pPlayerHpLabel);
	CC_SAFE_RELEASE_NULL(m_pLabel);
	CC_SAFE_RELEASE_NULL(m_pComboLabel);
	CC_SAFE_RELEASE_NULL(m_pAnime);
}

bool HudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	CCLOG("HudInit");
	CCSize screennSize = CCDirector::sharedDirector()->getWinSize();
	//ウィスプのHPラベルを追加
	m_pPlayerHpLabel = new CCLabelTTF();
	m_pPlayerHpLabel->initWithString("HP : 0", "arial", 18);
	m_pPlayerHpLabel->setColor(ccc3(127, 255, 212));
	//コンボカウントラベルを追加
	m_pComboLabel = new CCLabelTTF();
	m_pComboLabel->initWithString("0", "arial", 30.0);
	m_pComboLabel->setColor(ccc3(255, 215, 0));
	m_pComboLabel->setPosition(ccp(screennSize.width - (m_pComboLabel->getContentSize().width) - MARGIN, screennSize.height / 1.5 + MARGIN));
	m_pComboLabel->setVisible(false);
	
	this->addChild(m_pPlayerHpLabel);
	this->addChild(m_pComboLabel);
	m_pPlayerHpLabel->setPosition(ccp(screennSize.width / 4, screennSize.height / 1.2 + MARGIN));
	m_pPlayerHpLabel->setVisible(false);

	return true;
}


void HudLayer::damageToString(CCPoint hudPos, int damage)
{
	//ダメージラベルを追加
	CCString *label = new CCString();
	CCLabelTTF *damageLabel = new CCLabelTTF();
	damageLabel->initWithString("0", "arial", 25.0);
	damageLabel->setColor(ccc3(255, 165, 0));
	label->initWithFormat("%d", damage);
	this->addChild(damageLabel);
	damageLabel->setPosition(ccp(hudPos.x, hudPos.y + HUD_POS));
	damageLabel->setString(label->getCString());
	CCSpawn *color = CCSpawn::create(CCTintTo::create(0.5, 255, 215, 0), CCFadeOut::create(0.5), NULL);
	//カラー変更アクション後、削除するアクション
	CCSequence *seq = CCSequence::create(color, CCRemoveSelf::create(), NULL);
	damageLabel->runAction(seq);
}

void HudLayer::addComboCount()
{
	//コンボラベルを表示
	m_comboCount++;
	CCString *label = new CCString();
	label->initWithFormat("%d Hits", m_comboCount);
	m_pComboLabel->setString(label->getCString());
	m_pComboLabel->setVisible(true);
	//ヒットする毎にラベルが濃くなるアクション
	m_pComboLabel->runAction(CCTintBy::create(0.0, 0, -5, 10));
}

void HudLayer::hide()
{
	//ラベルを非表示にし、色を元に戻す
	m_pComboLabel->setVisible(false);
	m_pComboLabel->setColor(ccc3(255, 215, 0));
}

void HudLayer::drawHpLabel()
{
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//HPラベルを表示し、更新していく
	setLabelVisible(true);
	CCString *label = new CCString();
	label->initWithFormat("HP : %d", wisp->getHP());
	m_pPlayerHpLabel->setString(label->getCString());
}

void HudLayer::drawHpbar(GameObject *obj)
{
	//HPバーにダメージを反映させる
	CCProgressFromTo *draw = CCProgressFromTo::create(0.5, obj->getHP(), obj->getHpRatio());
	obj->getHpBar()->runAction(draw);
}

void HudLayer::initHpbar(GameObject *obj)
{
	//ウィスプのみ、リザルト状態でHPバーを最大に戻す
	if (OM::getInstance()->getStateMachine()->getStates().back()->getStateID() == "RESULT")
	{
		CCProgressFromTo *add = CCProgressFromTo::create(0, obj->getHP(), obj->getMaxHP());
		obj->getHpBar()->runAction(add);
		return;
	} 
	//HPバーの背景を追加
	CCSprite *hpBgBar = CCSprite::create("hpBarBg.png");
	hpBgBar->setPosition(ccp(obj->getContentSize().width / 2, obj->getContentSize().height / 10 - 10));
	obj->addChild(hpBgBar, z_hpBarBg, kTag_hpbarBg);
	//HPバーを追加
	obj->setHpBar(CCProgressTimer::create(CCSprite::create("hpBar.png")));
	CCProgressTimer *hpBar = obj->getHpBar();
	hpBar->setPosition(ccp(hpBgBar->getContentSize().width / 2, hpBgBar->getContentSize().height / 2));
	hpBar->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	hpBar->setMidpoint(ccp(0, 1));
	hpBar->setBarChangeRate(ccp(1, 0));
	hpBar->setPercentage(obj->getHpRatio());
	hpBgBar->addChild(hpBar, z_hpbar);
}

void HudLayer::setLabelVisible(bool flg)
{
	//HPラベルを非表示に
	m_pPlayerHpLabel->setVisible(flg); 
}

void HudLayer::ready()
{
	if (OM::getInstance()->getIsReady())
	{
		return;
	}
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//Readyラベルを追加
	CCSprite *ready = CCSprite::create("normal_ready.png");
	ready->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	//フェードインするため、透明に
	ready->setOpacity(0);
	this->addChild(ready);
	//フェードインし、1秒後にFireラベルを表示させ、Readyラベルを削除するアクション
	CCSequence *readyFire = CCSequence::create(CCFadeIn::create(0.5), CCDelayTime::create(1.0), CCCallFunc::create(this, callfunc_selector(HudLayer::fire)), CCRemoveSelf::create(), NULL);
	ready->runAction(readyFire);
}

void HudLayer::fire()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//Fireラベルを追加
	CCSprite *fire = CCSprite::create("normal_fire.png");
	fire->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
	this->addChild(fire);

	CCSpawn *scaleOut = CCSpawn::create(CCEaseIn::create(CCScaleTo::create(0.5, 2.0), 0.5), CCFadeOut::create(1), NULL);
	CCSequence *action = CCSequence::create(scaleOut, CCCallFunc::create(this, callfunc_selector(HudLayer::touchImage)),CCRemoveSelf::create(), NULL);
	fire->runAction(action);
	OM::getInstance()->setIsReady(true);
}

void HudLayer::aim()
{
	if (OM::getInstance()->getIsReady())
	{
		//Aimラベルを追加
		CCSprite *aim = CCSprite::create("normalState_aim.png");
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		aim->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 1.5));
		aim->setOpacity(0);
		this->addChild(aim);

		CCSequence *aimFade = CCSequence::create(CCFadeIn::create(0.5),
			CCFadeOut::create(0.5),
			CCCallFunc::create(this, callfunc_selector(HudLayer::touchImage)),
			CCRemoveSelf::create(), NULL);
		aim->runAction(aimFade);
	}
}

void HudLayer::touchImage()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//タッチイメージを追加
	CCSprite * touchImage = CCSprite::create("normalState_touch.png");
	touchImage->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	this->addChild(touchImage, z_touch, ktag_touch);
	CCSequence *fade = CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(fade);
	touchImage->runAction(repeat);
}