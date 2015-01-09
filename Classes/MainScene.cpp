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

//�V���b�g�p���[�{��
const float SHOT_POWER = 0.5;
//�E�B�X�v�̉ғ��͈�
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

	ObjectManager *om = ObjectManager::getInstance();
	om->init();
	scene->addChild(om);
	layer->_om = om;

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

	//�E�B�X�v�i�v���C���[�j�z�u
	_wisp = Player::create();

	//�GNPC�z�u
	_enemy = Enemy::create("enemy3.png", SHOT_POWER, SHOT_POWER);
	//Enemy::create("enemy3.png", 0.8, 0.3);
	//�V���O���^�b�v���[�h
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	//�Q�[�������[�v������
	this->scheduleUpdate();

    return true;
}

//��葬�x�ȏ�Ȃ�ڐG����
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
	
	//�E�B�X�v�̏�Ԃ��X�V
	setWispNextPosition(_wisp->getNextPosition());
	//�E�B�X�v�̐��i��
	setWispVector(_wisp->getVector());
	setWispVector(ccpMult(_wispVector, 0.98f));
	//�����蔻��
	//�GNPC�̐ݒ�
	setEnemyNextPosition(_enemy->getNextPosition());
	setEnemyVector(_enemy->getVector());

	float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
	float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());

	float distOne = _cm->Calc(pow(diffx, 2), pow(diffy, 2));
	float distTwo = _cm->Calc(pow(_wisp->getPositionX() - _enemyNextPosition.x, 2), pow(_wisp->getPositionY() - _enemyNextPosition.y, 2));

	//�Փ�
	//onCollision(distOne, distTwo, squared_radius);
	onCollision(distOne, distTwo, calcVector());


	//�Ō�ɁA�E�B�X�v�̐��i�͂Ǝ��̖ڕW�n�_�ɐݒ�
	_wisp->setVector(_wispVector);
	_wisp->setNextPosition(_wispNextPosition);

	//���̖ڕW�n�_�ֈړ�
	//_enemy->setPosition(_enemy->getNextPosition());
	_wisp->setPosition(_wisp->getNextPosition());

}


//���ˑO�̃E�B�X�v�̈ړ��͈͂𐧌�
CCPoint MainScene::calcPos(CCPoint touch){
	//�E�B�X�v�̏����ʒu�ƃ^�b�v�ʒu�̋���
	int dist = touch.getDistance(_wisp->getPosition());

	//dist��WISP_EXTEND�ȏ�ɂȂ�����
	if (gThanPos(dist))
		//������WISP_EXTEND�ƂȂ�ʒu��Ԃ��i�͈͐����j
		return calcRetPos(touch, dist);
	else
		//�^�b�v�ʒu��Ԃ�
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
	//�^�b�v�ʒu��WISP_EXTEND�O�ł���΁A���͈͓̔��Ɉʒu����悤�ɏ���
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
	//���̊p�x���v�Z
	float angle = ((wisp->getPosition() - wisp->getPosition()).getAngle());
	return angle;
}

CCPoint MainScene::extendPos(CCNode* wisp){
	//���̏I�_���v�Z
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
	//��1��\��
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
		//�����폜
		this->removeChildByTag(1);
		//�E�B�X�v�̈ʒu���v�Z
		wisp->setPosition(calcPos(touch->getLocation()));
	}
}

//�Փ˂ƌ�������
void MainScene::onCollision(float distOne, float distTwo, float radius){
	
	//�Փ˔���2�i�o�E���h���j
	if (_cm->isLessThanDist(distOne, radius) || _cm->isLessThanDist(distTwo, radius)) {
		CCLOG("secondHit");

		//�E�B�X�v�ƃG�l�~�[�̋������擾
		float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
		float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());
		//�E�B�X�v�ƓGNPC�̏Փˎ��̉^���ʂ��v�Z
		float mag_wisp = _cm->Calc(pow(_wispVector.x, 2), pow(_wispVector.y, 2));
		float mag_enemy = _cm->Calc(pow(_enemyVector.x, 2), pow(_enemyVector.y, 2));

		//�Փˎ��̖��C����
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
