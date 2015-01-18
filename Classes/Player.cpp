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
#include "EnemyAttack.h"
#include "EnemyState.h"
#include "ObjectManager.h"
#include "SimpleAudioEngine.h"
#include "ResultState.h"


USING_NS_CC;
using namespace CocosDenshion;


Player::Player()
	:_isDead(false)
	, _canFire(true)
	, _isAttacking(false)
	, _isContacted(false)
	, _touchPoint(ccp(0, 0))
	, _timer(0)
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

void Player::hitCheck()
{
	//敗北していたら抜ける
	if (_isDead)
	{
		return;
	}

	CCPoint wispPosition = this->getPosition();
	EnemyAttack *enemyAttack = static_cast<EnemyAttack *>(_main->getChildByTag(kTag_enemyAttack));
	//攻撃の当たり判定
	if (enemyAttack)
	{
		//敵の攻撃がウィスプの描画領域に触れたらtrue
		bool isContact = enemyAtkRect(enemyAttack).containsPoint(wispPosition);
		if (isContact)
		{
			CCLOG("wispHit");
			damage(enemyAttack);
			enemyAttack->removeFromParentAndCleanup(true);
		}
	}

}


CCRect Player::enemyAtkRect(EnemyAttack *enemyAttack)
{
	//敵NPC攻撃描画判定
	CCRect atkRect = CCRectMake(enemyAttack->getPositionX() - (enemyAttack->getContentSize().width / 10),
		enemyAttack->getPositionY() - (enemyAttack->getContentSize().height / 10),
		enemyAttack->getContentSize().width / 2, enemyAttack->getContentSize().height / 2);

	return atkRect;
}

void Player::damage(EnemyAttack *atk)
{
	//ダメージ
	int damage = atk->getAtk();

	if (damage > _hp)
	{
		//HPがマイナスに表示されるのを防ぐ
		_hp -= _hp;
	}
	else
	{
		_hp -= damage;
	}
	//HPラベルに反映
	Hud::getInstance()->drawMyHpLabel();
	Hud::getInstance()->damageToString(this->getPosition(), atk->getAtk());
	CCLOG("wispdamageHp%d", _hp);
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	_hud->getAnime()->swingAnime(this);
	if (_hp <= 0)
	{
		CCLOG("wispDied");
		setHP(0);
		setIsDead(true);
		_hud->getAnime()->wispDyingAnime(this);
	}
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
		_isContacted = false;
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

void Player::collisionBlockWest()
{
	if (gThanRadius(_nextPosition.x))
	{
		_nextPosition.x = this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void Player::collisionBlockEast()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.x, screenSize.width))
	{
		_nextPosition.x = screenSize.width - this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void Player::collisionBlockNorth()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.y, screenSize.height)) {
		_nextPosition.y = screenSize.height - this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}

}

void Player::collisionBlockSouth()
{
	if (gThanRadius(_nextPosition.y))
	{
		_nextPosition.y = this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	} 
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す
bool Player::gThanRadius(float wispNextPos)
{
	if (wispNextPos < this->radius())
	{
		return true;
	}
	return false;
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す
bool Player::lessThanRadius(float wispNextPos, float screenwh)
{
	if (wispNextPos > screenwh - this->radius())
	{
		return true;
	}
	return false;
}

void Player::resetWisp()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	setHP(100);
	setIsDead(false);
	setCanFire(true);
	setTimer(0);
	setVector(ccp(NULL, NULL));
	setPosition(ccp(screenSize.width * 0.5, this->radius() * 2));
}