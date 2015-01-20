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


USING_NS_CC;

Player::Player():
_canFire(true),
_isAttacking(false),
_touchPoint(ccp(0, 0)),
_timer(0)
{
	setHP(100);
	setMaxHP(100);
	setAtk(10);
}

Player::~Player(){}

Player* Player::create()
{
	Player * wisp = new Player();
	if (wisp)
	{
		wisp->initWisp();
		wisp->autorelease();
		Main::getInstance()->addChild(wisp, z_wisp, kTag_wisp);
		return wisp;
	}
	CC_SAFE_DELETE(wisp);
	return NULL;
}


Player* Player::initWisp()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	this->initWithFile("wisp_1.png");
	this->setPosition(ccp(screenSize.width * 0.5, this->radius() * 1));
	//フェードインのため、透明に
	this->setOpacity(0);
	//アニメーションの初期化
	_hud->getAnime()->wispInitAnime(this);
	//HPバーの追加
	_hud->initHpbar(this);

	//vectorとmapコンテナへウィスプを追加
	_om->addGameObjectMap("wisp", this);
	_om->addGameObject(this);

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
		_hud->drawMyHpLabel();
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
		CCLOG("wispresultExit");
		_hud->initHpbar(this);
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

void Player::addPower(int power)
{
	//パワーアップ
	this->_atk += power;
}

void Player::drawPower(int power)
{
	//パワーダウン
	this->_atk -= power;
}

void Player::addForceToWisp()
{
	//放した時の運動量をウィスプに加える
	_nextPosition.x += _vector.x;
	_nextPosition.y += _vector.y;
}


bool Player::wispTouchBegan()
{
	bool ret = false;
	CCTouch *touch = _main->getBeganTouch();
	if (!_canFire)
	{
		return ret;
	}
	
	if (touch)
	{
		//タッチ位置を取得
		setTouchPoint(touch->getLocation());
		//タッチ画像に触れているなら次の処理へ
		ret = toTheNext();
	}

	return ret;
}

void Player::wispTouchMoved()
{
	CCTouch* touch = _main->getMovedTouch();
	CCPoint movePoint = touch->getLocation();
	if (touch)
	{
		//ガイド矢印を追加
		createArrow(movePoint);
	}
}

void Player::wispTouchEnded()
{
	CCTouch* touch = _main->getEndedTouch();
	//放した座標
	CCPoint endPoint = touch->getLocation();
	//タッチ開始座標から放した座標の距離 * 0.5の値を計算し、力を加える
	this->setVector(calcForce(endPoint));
	//矢印を削除
	_main->removeChildByTag(kTag_arrow);
	//ショット中の操作を不可に
	setCanFire(false);
	setIsAttacking(true);
}

bool Player::toTheNext()
{
	bool ret = false;
	//タッチ画像に触れているなら次の処理へ
	CCSprite * touchImage = static_cast<CCSprite *>(_hud->getChildByTag(ktag_touch));
	if (touchImage && touchImage->boundingBox().containsPoint(_touchPoint))
	{
		//タッチ画像を削除
		touchImage->removeFromParent();
		ret = true;
	}

	return ret;
}

void Player::createArrow(CCPoint movePoint)
{
	CCSprite *arrow = static_cast<CCSprite *>(_main->getChildByTag(kTag_arrow));
	//存在しなければ、矢印を追加（１つしか作らないための処理）
	if (!arrow)
	{
		arrow = _hud->getAnime()->arrowAnime();
		_main->addChild(arrow, z_arrow, kTag_arrow);
	}
	//矢印の座標と角度の設定
	arrowSettings(arrow, movePoint);
}

void Player::arrowSettings(CCSprite *arrow, CCPoint movePoint)
{
	arrow->setPosition(this->getPosition());
	//タッチ開始座標に対する移動中のタッチ座標の角度
	float angle = ((_touchPoint - movePoint)).getAngle();
	CCPoint pos = movePoint + _touchPoint.rotate(CCPoint::forAngle(angle));
	angle = CC_RADIANS_TO_DEGREES((_touchPoint - pos).getAngle() * -1);
	//結果を矢印に反映
	arrow->setRotation(angle);
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	float diffx = _touchPoint.x - endPoint.x;
	float diffy = _touchPoint.y - endPoint.y;
	//タッチ開始座標から放した座標の距離 * 0.5の値を計算
	return ccp(diffx, diffy) * 0.5;
}

void Player::startTimer()
{
	//ショット後、タイマースタート
	if (!_canFire)
	{
		++_timer;
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
	setVector(ccp(NULL, NULL));
	setPosition(ccp(screenSize.width * 0.5, this->radius() * 2));
}