#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "CollisionManager.h"


USING_NS_CC;
using namespace CocosDenshion;

//�E�B�X�v�̉ғ��͈�
const float WISP_EXTEND = 50;

MainScene* MainScene::s_pInstance = 0;

MainScene::MainScene()
: _enemy(NULL)
, _wisp(NULL)
, _cm(NULL)
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
    
	//�X�N���[���T�C�Y���擾
	setScreenSize(CCDirector::sharedDirector()->getWinSize());
    
	//�w�i�摜
	CCSprite * background = CCSprite::create("background0.png");
	background->setPosition(ccp(_screenSize.width / 2.0, _screenSize.height / 2.0));
	this->addChild(background);

	//�E�B�X�v�i�v���C���[�j�z�u
	_wisp = ObjectSprite::create("wisp_1.png");
	_wisp->setPosition(ccp(_screenSize.width * 0.5, _wisp->radius() * 2));
	_wisp->setTag(1);
	this->addChild(_wisp);

	//�GNPC�z�u
	_enemy = ObjectSprite::create("enemy1.png");
	_enemy->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 - 2 * _enemy->radius()));
	_enemy->setTag(2);
	this->addChild(_enemy);

	

	//�V���O���^�b�v���[�h
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	//�Q�[�������[�v������
	this->scheduleUpdate();

    return true;
}

void MainScene::update(float dt) {

	//�E�B�X�v�̏�Ԃ��X�V
	setWispNextPosition(_wisp->getNextPosition());
	//�E�B�X�v�̐��i��
	setWispVector(_wisp->getVector());
	setWispVector(ccpMult(_wispVector, 0.98f));
	//�E�B�X�v�ɗ͂�������
	addForceToWisp();
	//�����蔻��
	float squared_radius = pow(_enemy->radius() + _wisp->radius(), 2);
	//�GNPC�̐ݒ�
	setEnemyNextPosition(_enemy->getNextPosition());
	setEnemyVector(_enemy->getVector());

	float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
	float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());

	float distOne = _cm->Calc(pow(diffx, 2), pow(diffy, 2));
	float distTwo = _cm->Calc(pow(_wisp->getPositionX() - _enemyNextPosition.x, 2), pow(_wisp->getPositionY() - _enemyNextPosition.y, 2));

	//�Փ�
	onCollision(distOne, distTwo, squared_radius);


	//�E�B�X�v�ƕǂ̏Փ˔���
	//��
	collisionBlockWest();
	//��
	collisionBlockEast();
	//�k
	collisionBlockNorth();
	//��
	collisionBlockSouth();


	//�Ō�ɁA�E�B�X�v�̐��i�͂Ǝ��̖ڕW�n�_�ɐݒ�
	_wisp->setVector(_wispVector);
	_wisp->setNextPosition(_wispNextPosition);

	//���̖ڕW�n�_�ֈړ�
	_enemy->setPosition(_enemy->getNextPosition());
	_wisp->setPosition(_wisp->getNextPosition());

}

CCNode* MainScene::getWispTag(){
	return this->getChildByTag(0);
}

CCNode* MainScene::getEnemyTag(){
	return this->getChildByTag(1);
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

	bool ret = false;
	if (touch) {
		//�^�b�`�ʒu���擾
		_touchPoint = touch->getLocation();
		//�E�B�X�v�ɐG��Ă���Ȃ玟�̏�����
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
		//���������|�C���g�ƍ���\��
		setChainOne(initChainOne(chain), extPos);
	}

}


void MainScene::ccTouchEnded(CCTouch* touch, CCEvent* event){

	CCNode* wisp = getChildByTag(0);
	CCPoint endPoint = touch->getLocation();
	CCPoint force = CCPoint(_touchPoint.x - endPoint.x, _touchPoint.y - endPoint.y) * 0.5;
	_wisp->setVector(force);
	//�����폜���A�E�B�X�v�ɗ͂�������
	//removeAndAdd(wisp, touch);
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
	if (_cm->isLessThanDist(distOne, radius) || _cm->isLessThanDist(distTwo, radius)) {

		float diffx = _cm->CalcDiff(_wispNextPosition.x, _enemy->getPositionX());
		float diffy = _cm->CalcDiff(_wispNextPosition.y, _enemy->getPositionY());

		float mag_ball = _cm->Calc(pow(_wispVector.x, 2), pow(_wispVector.y, 2));
		float mag_player = _cm->Calc(pow(_enemyVector.x, 2), pow(_enemyVector.y, 2));

		float force = sqrt(mag_ball + mag_player);
		float angle = atan2(diffy, diffx);

		_wispVector.x = force * cos(angle);
		_wispVector.y = (force * sin(angle));

		_wispNextPosition.x = _enemyNextPosition.x + (_enemy->radius() + _wisp->radius() + force) * cos(angle);
		_wispNextPosition.y = _enemyNextPosition.y + (_enemy->radius() + _wisp->radius() + force) * sin(angle);

		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system48.mp3");
	}
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ�
bool MainScene::gThanRadius(float ballNextPos){
	if (ballNextPos < _wisp->radius())
		return true;
	return false;
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ�
bool MainScene::lessThanRadius(float ballNextPos, float screenwh){
	if (ballNextPos > screenwh - _wisp->radius())
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
