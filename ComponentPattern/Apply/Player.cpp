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
const float SHOT_RATE = 0.3;
//ウィスプのHP
const int WISP_HP = 1;
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
	this->setHP(WISP_HP);
	this->setMaxHP(WISP_MAXHP);
	this->setAtkPower(WISP_ATK); 
}

Player::~Player(){}

Player* Player::create()
{
	Player * wisp = new Player();
	if (wisp)
	{
		wisp->initWisp();
		wisp->autorelease();
		//MainSceneのインスタンスを取得し、そこに追加
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
	//x軸は中央へ、y軸は底からウィスプの半径1つ分空けた座標へ配置
	this->setPosition(ccp(screenSize.width * 0.5, this->getRadius() * 1.0));
	//フェードインのため、透明に
	this->setOpacity(0);
	//アニメーションの初期化
	Hud::getInstance()->getAction()->wispInitAction(this);
	//HPバーの追加
	Hud::getInstance()->initHpBar(this);
	//vectorコンテナへウィスプを追加
	OM::getInstance()->addGameObject(this);

	return this;
}


void Player::onStateEnter()
{	
	//現在の状態のIDを代入
	this->setStateID();
	if (this->isNormalState())
	{
		//プレイヤーのターン開始時の初期化
		setTouchPoint(ccp(0, 0));
		setTimer(0);
		setCanFire(true);
		//HPラベルの表示
		Hud::getInstance()->drawHpLabel();
	}
	else if (this->isEnemyState())
	{
		
	}
	else if (this->isResultState())
	{
		
	}
}

void Player::onStateExit()
{
	if (this->isNormalState())
	{
		setIsAttacking(false);
		this->setAcceleration(ccp(0, 0));
	} 
	else if (this->isResultState())
	{
		Hud::getInstance()->initHpBar(this);
	}
}

void Player::stateUpdate(float dt)
{
	//AudioComponentから効果音を呼び出す
	this->m_pAudio->update(dt, this);
	//敗北していたら以降の処理を行なわない
	if (this->m_isDead)
	{
		return;
	}
	//ウィスプに力を加える
	addForceToWisp();
	//衝突判定
	activateCollision();
	//攻撃後、次の状態へのカウント開始
	startTimer();
}

bool Player::wispTouchBegan()
{
	bool ret = false;
	CCTouch *touch = MS::getInstance()->getBeganTouch();
	//攻撃可能で無ければ以降の処理を行なわない
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
	//タッチの座標を取得
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
	//タッチ開始座標から放した座標の距離 * SHOT_RATEの値を計算し、力を加える
	this->setAcceleration(calcForce(endPoint));
	//矢印を削除
	//MS::getInstance()->removeChildByTag(kTag_arrow);
	removeArrow();
	//ショット中の操作を不可に
	setCanFire(false);
	setIsAttacking(true);
}

void Player::activateCollision()
{
	//衝突判定（敵NPCの攻撃）
	this->hitCheck();
	//ウィスプと壁の衝突判定
	//西
	this->collisionBlockWest();
	//東
	this->collisionBlockEast();
	//北
	this->collisionBlockNorth();
	//南
	this->collisionBlockSouth();
}

void Player::addPower(int power)
{
	//パワーアップ
	this->m_atkPower += power;
}

void Player::drawPower(int power)
{
	//パワーダウン
	this->m_atkPower -= power;
}

void Player::addForceToWisp()
{
	//放した時の運動量をウィスプに加える
	this->m_nextPosition.x += this->m_acceleration.x;
	this->m_nextPosition.y += this->m_acceleration.y;
}

bool Player::isNext()
{
	bool ret = false;
	//MainSceneからtouchImageのノードをキャストして取得
	CCSprite * touchImage = static_cast<CCSprite *>(Hud::getInstance()->getChildByTag(ktag_touch));
	//タッチ画像に触れているなら次の処理へ
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
		arrow = Hud::getInstance()->getAction()->arrowAction();
		MS::getInstance()->addChild(arrow, z_arrow, kTag_arrow);
	}
	//矢印の座標と角度の設定
	arrowSettings(arrow, movePoint);
}

void Player::arrowSettings(CCSprite *arrow, CCPoint movePoint)
{
	arrow->setPosition(this->getPosition());
	//タッチ開始座標に対する移動中のタッチ座標の角度
	//ベクトル（m_touchPoint - movePoint）とx軸間の角度を弧度で算出
	m_angle = ((m_touchPoint - movePoint)).getAngle();
	//操作範囲のベクトルを返す
	CCPoint point = movePoint + m_touchPoint.rotate(CCPoint::forAngle(m_angle));
	//弧度から度への変換
	m_angle = CC_RADIANS_TO_DEGREES((m_touchPoint - point).getAngle() * -1.0);
	CCLOG("angle : %f", m_angle);
	//結果を矢印に反映
	arrow->setRotation(m_angle);
}

void Player::removeArrow()
{
	CCSprite *arrow = static_cast<CCSprite *>(MS::getInstance()->getChildByTag(kTag_arrow));
	if (arrow)
	{
		//ガイド矢印が存在するなら、MainSceneから削除
		arrow->removeFromParent();
	}
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	//タッチ開始座標から放した座標の距離
	float diffx = m_touchPoint.x - endPoint.x;
	float diffy = m_touchPoint.y - endPoint.y;
	//角度帯毎にブレを補正した値 * SHOT_RATEの値を計算
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
	this->setHP(100);
	this->setIsDead(false);
	setCanFire(true);
	setTimer(0);
	this->setAcceleration(ccp(0, 0));
	this->setPosition(ccp(screenSize.width / 2.0, this->getRadius() * 2.0));
}