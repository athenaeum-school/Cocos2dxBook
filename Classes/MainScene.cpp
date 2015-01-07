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
    
	//スクリーンサイズを取得
	setScreenSize(CCDirector::sharedDirector()->getWinSize());
    
	//背景画像
	CCSprite * background = CCSprite::create("background0.png");
	background->setPosition(ccp(_screenSize.width / 2.0, _screenSize.height / 2.0));
	this->addChild(background);

	//ウィスプ（プレイヤー）配置
	_wisp = ObjectSprite::create("wisp_1.png");
	_wisp->setPosition(ccp(_screenSize.width * 0.5, _wisp->radius() * 2));
	_wisp->setTag(1);
	this->addChild(_wisp, z_wisp);

	//敵NPC配置
	_enemy = ObjectSprite::create("enemy3.png");
	_enemy->setPosition(ccp(_screenSize.width * SHOT_POWER, _screenSize.height * SHOT_POWER - 2 * _enemy->radius()));
	_enemy->setTag(2);
	this->addChild(_enemy, z_enemy);

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

	if (_wispVector.x < 0.1f && _wispVector.y < 0.1f && !_canFire) {
		setWispVector(ccp(0, 0));
		setCanFire(true);
	}

	//ウィスプの状態を更新
	setWispNextPosition(_wisp->getNextPosition());
	//ウィスプの推進力
	setWispVector(_wisp->getVector());
	setWispVector(ccpMult(_wispVector, 0.98f));
	//ウィスプに力を加える
	addForceToWisp();
    //当たり判定
	//float squared_radius = pow(_enemy->radius() + _wisp->radius(), 2);
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


	//ウィスプと壁の衝突判定
	//西
	collisionBlockWest();
	//東
	collisionBlockEast();
	//北
	collisionBlockNorth();
	//南
	collisionBlockSouth();


	//最後に、ウィスプの推進力と次の目標地点に設定
	_wisp->setVector(_wispVector);
	_wisp->setNextPosition(_wispNextPosition);

	//次の目標地点へ移動
	_enemy->setPosition(_enemy->getNextPosition());
	_wisp->setPosition(_wisp->getNextPosition());

}


float MainScene::cGetWispVectorX(){
	return this->_wispVector.x;
}

float MainScene::cGetWispVectorY(){
	return this->_wispVector.y;
}


void MainScene::cSetwispNextPositionX(float f){
	this->_wispNextPosition.x += f;
}

void MainScene::cSetwispNextPositionY(float f){
	this->_wispNextPosition.y += f;
}

CCNode* MainScene::getWispTag(){
	return this->getChildByTag(0);
}

CCNode* MainScene::getEnemyTag(){
	return this->getChildByTag(1);
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

	bool ret = false;
	if (!_canFire) return false;
	if (touch) {
		_isContacted = false;
		//タッチ位置を取得
		_touchPoint = touch->getLocation();
		//ウィスプに触れているなら次の処理へ
		if (_wisp->boundingBox().containsPoint(_touchPoint)) {
			ret = true;
		}
	}
	return ret;
}

void MainScene::ccTouchMoved(CCTouch* touch, CCEvent* event){
	
	CCNode *wisp = getChildByTag(0);
	CCNode *chain = getChildByTag(1);

	if (wisp)
	{
		CCPoint extPos = extendPos(wisp);
		//鎖を引くポイントと鎖を表示
		setChainOne(initChainOne(chain), extPos);
	}

}


void MainScene::ccTouchEnded(CCTouch* touch, CCEvent* event){

	CCNode* wisp = getChildByTag(0);
	CCPoint endPoint = touch->getLocation();
	CCPoint force = CCPoint(_touchPoint.x - endPoint.x, _touchPoint.y - endPoint.y) * 0.5;
	_wisp->setVector(force);
	//鎖を削除し、ウィスプに力を加える
	//removeAndAdd(wisp, touch);
	//ショット中の操作を不可に
	setCanFire(false);
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

void MainScene::damageToEnemy(){
	CCLOG("damage");
	//ダメージ時、スターエフェクト表示
	CCSprite *star = CCSprite::create("star1.png");
	star->setPosition(_wisp->getPosition());
	addChild(star, z_star);

	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("star1.png");
	animation->addSpriteFrameWithFileName("star2.png");
	animation->addSpriteFrameWithFileName("star3.png");
	animation->addSpriteFrameWithFileName("star4.png");
	animation->setDelayPerUnit(0.1);

	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), CCFadeOut::create(0.45), nullptr);
	CCSequence *starSequence = CCSequence::create(spawn, CCRemoveSelf::create(), nullptr);

	star->runAction(CCScaleTo::create(0.4, 2));
	star->runAction(starSequence);
	
	//ダメージ時、敵NPCをスイング
	CCRepeat *swing = CCRepeat::create(CCSequence::create(CCRotateTo::create(0.1, -10), CCRotateTo::create(0.1, 10), NULL), 4);
	_enemy->runAction(CCSequence::create(swing, CCRotateTo::create(0, 0.125), NULL));

	
	//ダメージ時、爆発エフェクト表示
	CCSprite *ex = CCSprite::create("explode1.png");
	ex->setPosition(_enemy->getPosition());
	addChild(ex, z_explode);

	CCAnimation *explode = CCAnimation::create();
	explode->addSpriteFrameWithFileName("explode1.png");
	explode->addSpriteFrameWithFileName("explode2.png");
	explode->addSpriteFrameWithFileName("explode3.png");
	explode->addSpriteFrameWithFileName("explode4.png");
	explode->setDelayPerUnit(0.1);

	CCSpawn *exSpawn = CCSpawn::create(CCAnimate::create(explode), CCFadeOut::create(0.45), nullptr);
	CCSequence *exSequence = CCSequence::create(exSpawn, CCRemoveSelf::create(), nullptr);

	ex->runAction(exSequence);

}


//衝突と減速処理
void MainScene::onCollision(float distOne, float distTwo, float radius){
	//衝突判定1（通過時）
	CCPoint wispPosition = _wisp->getPosition();
	CCRect enemyRect = _enemy->boundingBox();
	bool isContact = enemyRect.containsPoint(wispPosition);
	if (isContact && !_isContacted){
		CCLOG("firstHit");
		damageToEnemy();
		_isContacted = true;
	}
	else if (!isContact){
		_isContacted = false;
	}
		
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

		damageToEnemy();
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system48.mp3");
	}
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す
bool MainScene::gThanRadius(float wispNextPos){
	if (wispNextPos < _wisp->radius())
		return true;
	return false;
}

//ウィスプの半径が壁を超えたら、衝突する判定を返す
bool MainScene::lessThanRadius(float wispNextPos, float screenwh){
	if (wispNextPos > screenwh - _wisp->radius())
		return true;
	return false;
}

void MainScene::collisionBlockWest(){
	if (gThanRadius(_wispNextPosition.x)) {
		_wispNextPosition.x = _wisp->radius();
		_wispVector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void MainScene::collisionBlockEast(){
	if (lessThanRadius(_wispNextPosition.x, _screenSize.width)) {
		_wispNextPosition.x = _screenSize.width - _wisp->radius();
		_wispVector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void MainScene::collisionBlockNorth(){
	if (lessThanRadius(_wispNextPosition.y, _screenSize.height)) {
		_wispNextPosition.y = _screenSize.height - _wisp->radius();
		_wispVector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void MainScene::collisionBlockSouth(){
	if (gThanRadius(_wispNextPosition.y)) {
		_wispNextPosition.y = _wisp->radius();
		_wispVector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void MainScene::addForceToWisp(){
	_wispNextPosition.x += _wispVector.x;
	_wispNextPosition.y += _wispVector.y;
}
