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
	CCTouch *touch = _main->getBeganTouch();
	CCNode *wisp = _main->getChildByTag(kTag_wisp);
	
	if (!_canFire)
	{
		return false;
	}
	
	if (touch)
	{
		//タッチ位置を取得
		_touchPoint = touch->getLocation();
		//ウィスプに触れているなら次の処理へ
		if (wisp->boundingBox().containsPoint(_touchPoint)) 
		{
			CCLOG("OK");
			return true;
		}
	}
}

void Player::wispTouchMoved()
{
	CCTouch* touch = _main->getMovedTouch();
	CCNode* wisp = _main->getChildByTag(kTag_wisp);
	
	if (wisp){}
}

void Player::wispTouchEnded()
{
	CCTouch* touch = _main->getEndedTouch();
	CCNode* wisp = _main->getChildByTag(kTag_wisp);
	//放した座標
	CCPoint endPoint = touch->getLocation();
	//タッチ開始座標から放した座標の距離 * 0.5の値を計算し、力を加える
	this->setVector(calcForce(endPoint));
	//ショット中の操作を不可に
	setCanFire(false);
	setIsAttacking(true);
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	//タッチ開始座標から放した座標の距離 * 0.5の値を計算
	return CCPoint(_touchPoint.x - endPoint.x, _touchPoint.y - endPoint.y) * 0.5;
}

void Player::startTimer()
{
	//ショット後、タイマースタート
	if (!getCanFire()){
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