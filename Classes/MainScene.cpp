/*
* MainScene.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "CollisionManager.h"


USING_NS_CC;
using namespace CocosDenshion;

//ショットパワー倍率
const float SHOT_POWER = 0.5;
//ウィスプの稼動範囲
const float WISP_EXTEND = 50;

MainScene* MainScene::s_pInstance = 0;

MainScene::MainScene()
: _enemy(NULL)
, _wisp(NULL)
, _cm(NULL)
, _canFire(true)
, _isContacted(false)
{
}

MainScene:: ~MainScene(){
	
}

CCScene* MainScene::createScene()
{
    CCScene *scene = CCScene::create();
    MainScene *layer = MainScene::create();
	scene->addChild(layer);

	CollisionManager *cm = CollisionManager::getInstance();
	cm->init();
	scene->addChild(cm);
	layer->_cm = cm;

    return scene;
}

bool MainScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	MainScene::s_pInstance = this;

	//スクリーンサイズを取得
	setScreenSize(CCDirector::sharedDirector()->getWinSize());
    
	//背景画像
	CCSprite * background = CCSprite::create("background0.png");
	background->setPosition(ccp(_screenSize.width / 2.0, _screenSize.height / 2.0));
	this->addChild(background);

	//ウィスプ（プレイヤー）配置
	_wisp = Player::create();

	//敵NPC配置
	_enemy = Enemy::create("enemy3.png", SHOT_POWER, SHOT_POWER);
	//Enemy::create("enemy3.png", 0.8, 0.3);
	//シングルタップモード
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	//ゲームをループさせる
	this->scheduleUpdate();

    return true;
}

//一定速度以上なら接触判定
float MainScene::calcVector(){
	/*if ((float)(_wisp->getPositionX() - _wispNextPosition.x <= 1)){
		if ((float)(_wisp->getPositionY() - _wispNextPosition.y <= 1)){
			if (_wispVector.x > 5, _wispVector.y > 5){
				float squared_radius = pow(_enemy->radius() + _wisp->radius(), 2);
				return squared_radius;
			}
		}
	}else*/ 
	if (_wispVector.x < 10, _wispVector.y < 10){
		return 0;
	}

		float squared_radius = pow(_enemy->radius() + _wisp->radius(), 2);
		return squared_radius;
}

void MainScene::update(float dt) {
	_wisp->stateUpdate(dt);
	
	//ウィスプの状態を更新
	setWispNextPosition(_wisp->getNextPosition());
	//ウィスプの推進力
	setWispVector(_wisp->getVector());
	setWispVector(ccpMult(_wispVector, 0.98f));
	//当たり判定
	//敵NPCの設定
	setEnemyNextPosition(_enemy->getNextPosition());
	setEnemyVector(_enemy->getVector());

	float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
	float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());

	float distOne = _cm->Calc(pow(diffx, 2), pow(diffy, 2));
	float distTwo = _cm->Calc(pow(_wisp->getPositionX() - _enemyNextPosition.x, 2), pow(_wisp->getPositionY() - _enemyNextPosition.y, 2));

	//衝突
	//onCollision(distOne, distTwo, squared_radius);
	onCollision(distOne, distTwo, calcVector());


	//最後に、ウィスプの推進力と次の目標地点に設定
	_wisp->setVector(_wispVector);
	_wisp->setNextPosition(_wispNextPosition);

	//次の目標地点へ移動
	//_enemy->setPosition(_enemy->getNextPosition());
	_wisp->setPosition(_wisp->getNextPosition());

}


//発射前のウィスプの移動範囲を制御
CCPoint MainScene::calcPos(CCPoint touch){
	//ウィスプの初期位置とタップ位置の距離
	int dist = touch.getDistance(_wisp->getPosition());

	//distがWISP_EXTEND以上になったら
	if (gThanPos(dist))
		//距離がWISP_EXTENDとなる位置を返す（範囲制限）
		return calcRetPos(touch, dist);
	else
		//タップ位置を返す
		return touch;
}

bool MainScene::gThanPos(int dist){
	if (dist > WISP_EXTEND)
		return true;
	return false;
}


CCPoint MainScene::calcRetPos(CCPoint touch, int dist){
	assert(dist != NULL);
	CCPoint wispPos = _wisp->getPosition();
	//タップ位置がWISP_EXTEND外であれば、その範囲内に位置するように処理
	return wispPos + (touch - wispPos) * WISP_EXTEND / dist;
}


bool MainScene::ccTouchBegan(CCTouch* touch, CCEvent* event){
	setBeganTouch(touch);
	return _wisp->wispTouchBegan();
}

void MainScene::ccTouchMoved(CCTouch* touch, CCEvent* event){
	setMovedTouch(touch);
	_wisp->wispTouchMoved();
}


void MainScene::ccTouchEnded(CCTouch* touch, CCEvent* event){
	setEndedTouch(touch);
	_wisp->wispTouchEnded();
}

float MainScene::extendAngle(CCNode* wisp){
	//鎖の角度を計算
	float angle = ((wisp->getPosition() - wisp->getPosition()).getAngle());
	return angle;
}

CCPoint MainScene::extendPos(CCNode* wisp){
	//鎖の終点を計算
	CCPoint pos = wisp->getPosition().rotate(CCPoint::forAngle(extendAngle(wisp)));
	return pos;
}

void MainScene::setChainOne(CCNode* chain1, CCPoint pos){
	CCNode *wisp = getChildByTag(0);
	chain1->setPosition(wisp->getPosition());
	chain1->setRotation(CC_RADIANS_TO_DEGREES((chain1->getPosition() - pos).getAngle() * -1));
	chain1->setScaleX(chain1->getPosition().getDistance(pos));
	chain1->setScaleY(10);
}

CCNode* MainScene::initChainOne(CCNode* chain1){
	//鎖1を表示
	if (!chain1)
	{
		chain1 = CCSprite::create("iron.png");
		chain1->setTag(1);
		//chain1->setZOrder(_gameL->kOrder_Chain1);
		this->addChild(chain1);
	}
	return chain1;
}

void MainScene::removeAndAdd(CCNode* wisp, CCTouch* touch){
	if (wisp)
	{
		//鎖を削除
		this->removeChildByTag(1);
		//ウィスプの位置を計算
		wisp->setPosition(calcPos(touch->getLocation()));
	}
}

//衝突と減速処理
void MainScene::onCollision(float distOne, float distTwo, float radius){
	
	//衝突判定2（バウンド時）
	if (_cm->isLessThanDist(distOne, radius) || _cm->isLessThanDist(distTwo, radius)) {
		CCLOG("secondHit");

		//ウィスプとエネミーの距離を取得
		float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
		float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());
		//ウィスプと敵NPCの衝突時の運動量を計算
		float mag_wisp = _cm->Calc(pow(_wispVector.x, 2), pow(_wispVector.y, 2));
		float mag_enemy = _cm->Calc(pow(_enemyVector.x, 2), pow(_enemyVector.y, 2));

		//衝突時の摩擦調整
		//float force = sqrt(mag_wisp + mag_enemy) * 0.5;
		float force = sqrt(mag_wisp + mag_enemy) * 0.8f;
		float angle = atan2(diffy, diffx);

		_wispVector.x = force * cos(angle);
		_wispVector.y = (force * sin(angle));

		_wispNextPosition.x = _enemyNextPosition.x + (_enemy->radius() + _wisp->radius() + force) * cos(angle);
		_wispNextPosition.y = _enemyNextPosition.y + (_enemy->radius() + _wisp->radius() + force) * sin(angle);

		_cm->damageToEnemy();
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system48.mp3");
	}
}
