/*
* Player.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "Player.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;
//ショット時の運動量倍率
const float SHOT_RATE = 0.4;
//ウィスプのHP
const int WISP_HP = 100;
//最大HP
const int WISP_MAXHP = 100;
//攻撃力
const int WISP_ATK = 10;

Player::Player():
m_canFire(true),
m_isAttacking(false),
m_touchPoint(ccp(0, 0)),
m_timer(0),
m_angle(0)
{
	setHP(WISP_HP);
	setMaxHP(WISP_MAXHP);
	setAtk(WISP_ATK); 
}

Player::~Player(){}

Player* Player::create()
{
	Player * wisp = new Player();
	if (wisp)
	{
		wisp->initWisp();
		wisp->autorelease();
		MS::getInstance()->addChild(wisp, z_wisp, kTag_wisp);
		return wisp;
	}
	CC_SAFE_DELETE(wisp);
	return NULL;
}

Player* Player::initWisp()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	this->initWithFile("wisp_1.png");
	this->setPosition(ccp(screenSize.width * 0.5, this->radius() * 1.0));
	//フェードインのため、透明に
	this->setOpacity(0);
	//アニメーションの初期化
	Hud::getInstance()->getAnime()->wispInitAnime(this);
	//HPバーの追加
	Hud::getInstance()->initHpbar(this);

	//vectorとmapコンテナへウィスプを追加
	OM::getInstance()->addGameObject(this);

	return this;
}


void Player::onStateEnter()
{	
	setStateID();
	if (isNormalState())
	{
		setTouchPoint(ccp(0, 0));
		setTimer(0);
		setCanFire(true);
		//HPラベルの表示
		Hud::getInstance()->drawHpLabel();
	}
	else if (isEnemyState())
	{
		
	}
	else if (isResultState())
	{
		
	}
}

void Player::onStateExit()
{
	if (isNormalState())
	{
		setIsAttacking(false);
		setVector(ccp(0, 0));
	} 
	else if (isResultState())
	{
		Hud::getInstance()->initHpbar(this);
	}
}

void Player::stateUpdate(float dt)
{
	//当たり判定確認
	hitCheck();
	//ウィスプに力を加える
	addForceToWisp();
	//ウィスプと壁の衝突判定
	//西
	collisionBlockWest();
	//東
	collisionBlockEast();
	//北
	collisionBlockNorth();
	//南
	collisionBlockSouth();
	
	//攻撃後、次の状態へのカウント開始
	startTimer();
}

bool Player::wispTouchBegan()
{
	bool ret = false;
	CCTouch *touch = MS::getInstance()->getBeganTouch();
	if (!m_canFire)
	{
		return ret;
	}
	
	if (touch)
	{
		//タッチ位置を取得
		setTouchPoint(touch->getLocation());
		//タッチ画像に触れているなら次の処理へ
		ret = isNext();
	}

	return ret;
}

void Player::wispTouchMoved()
{
	CCTouch* touch = MS::getInstance()->getMovedTouch();
	CCPoint movePoint = touch->getLocation();
	if (touch)
	{
		//ガイド矢印を追加
		createArrow(movePoint);
	}
}

void Player::wispTouchEnded()
{
	CCTouch* touch = MS::getInstance()->getEndedTouch();
	//放した座標
	CCPoint endPoint = touch->getLocation();
	//タッチ開始座標から放した座標の距離 * 0.5の値を計算し、力を加える
	this->setVector(calcForce(endPoint));
	//矢印を削除
	MS::getInstance()->removeChildByTag(kTag_arrow);
	//ショット中の操作を不可に
	setCanFire(false);
	setIsAttacking(true);
}

void Player::addPower(int power)
{
	//パワーアップ
	this->m_atk += power;
}

void Player::drawPower(int power)
{
	//パワーダウン
	this->m_atk -= power;
}

void Player::addForceToWisp()
{
	//放した時の運動量をウィスプに加える
	m_nextPosition.x += m_vector.x;
	m_nextPosition.y += m_vector.y;
}

bool Player::isNext()
{
	bool ret = false;
	//タッチ画像に触れているなら次の処理へ
	CCSprite * touchImage = static_cast<CCSprite *>(Hud::getInstance()->getChildByTag(ktag_touch));
	if (touchImage && touchImage->boundingBox().containsPoint(m_touchPoint))
	{
		//タッチ画像を削除
		touchImage->removeFromParent();
		ret = true;
	}

	return ret;
}

void Player::createArrow(CCPoint movePoint)
{
	CCSprite *arrow = static_cast<CCSprite *>(MS::getInstance()->getChildByTag(kTag_arrow));
	//存在しなければ、矢印を追加（１つしか作らないための処理）
	if (!arrow)
	{
		arrow = Hud::getInstance()->getAnime()->arrowAnime();
		MS::getInstance()->addChild(arrow, z_arrow, kTag_arrow);
	}
	//矢印の座標と角度の設定
	arrowSettings(arrow, movePoint);
}

void Player::arrowSettings(CCSprite *arrow, CCPoint movePoint)
{
	arrow->setPosition(this->getPosition());
	//タッチ開始座標に対する移動中のタッチ座標の角度
	m_angle = ((m_touchPoint - movePoint)).getAngle();
	CCPoint point = movePoint + m_touchPoint.rotate(CCPoint::forAngle(m_angle));
	m_angle = CC_RADIANS_TO_DEGREES((m_touchPoint - point).getAngle() * -1.0);
	CCLOG("angle : %f", m_angle);
	//結果を矢印に反映
	arrow->setRotation(m_angle);
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	//タッチ開始座標から放した座標の距離 * 0.5の値を計算
	float diffx = m_touchPoint.x - endPoint.x;
	float diffy = m_touchPoint.y - endPoint.y;
	//角度帯毎にブレを補正
	if (m_angle > -10.0 && m_angle < 10.0)
	{
		CCLOG("top");
		return ccp(diffx - 30, diffy) * SHOT_RATE;
	}
	else if (m_angle > 160)
	{
		CCLOG("bottomRight");
		return ccp(diffx + 45, diffy + 15) * SHOT_RATE;
	}
	else if (m_angle < -160)
	{
		CCLOG("bottomLeft");
		return ccp(diffx + 60, diffy - 45) * SHOT_RATE;
	}
	else if (m_angle < -91.0)
	{
		CCLOG("mAngle%f", m_angle);
		CCLOG("leftlow");
		return ccp(diffx + 30, diffy - 30) * SHOT_RATE;
	}
	else if (m_angle > 91.0 && m_angle < 180)
	{
		CCLOG("mAngle%f", m_angle);
		CCLOG("rightlow");
		return ccp(diffx + 15, diffy + 15) * SHOT_RATE;
	}
	return ccp(diffx - 15, diffy) * SHOT_RATE;
}

void Player::startTimer()
{
	//ショット後、タイマースタート
	if (!m_canFire)
	{
		++m_timer;
	}
}

void Player::resetWisp()
{
	//リトライ後の再設定
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	setHP(100);
	setIsDead(false);
	setCanFire(true);
	setTimer(0);
	setVector(ccp(0, 0));
	setPosition(ccp(screenSize.width / 2.0, this->radius() * 2.0));
}