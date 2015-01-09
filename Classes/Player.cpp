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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Player::Player(MainScene *main)
	:GameObject(main)
	, _canFire(true)
	, _isContacted(false)
	, _touchPoint(ccp(NULL, NULL))
{
}


Player::~Player()
{
}

Player* Player::create(){
	Player * wisp = new Player(Main::getInstance());
	if (wisp){
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

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile("wisp_1.png");
	this->setPosition(ccp(screenSize.width * 0.5, this->radius() * 2));
	
	Om::getInstance()->addGameObjectMap("wisp", this);
	Om::getInstance()->addGameObject(this);

	return this;
}

void Player::stateUpdate(float dt){
	stopWithSet();

	onCollisionPassing();
	/*Player * wisp = static_cast<Player *>(_main->getWispTag());

	//�E�B�X�v�̏�Ԃ��X�V
	setWispNextPosition(wisp->getNextPosition());
	//�E�B�X�v�̐��i��
	setWispVector(wisp->getVector());
	setWispVector(ccpMult(_wispVector, 0.98f)); */

	//�E�B�X�v�ɗ͂�������
	addForceToWisp();
	//�E�B�X�v�ƕǂ̏Փ˔���
	//��
	collisionBlockWest();
	//��
	collisionBlockEast();
	//�k
	collisionBlockNorth();
	//��
	collisionBlockSouth();

	/*//�Ō�ɁA�E�B�X�v�̐��i�͂Ǝ��̖ڕW�n�_�ɐݒ�
	setVector(_wispVector);
	setNextPosition(_wispNextPosition);

	//���̖ڕW�n�_�ֈړ�
	//_enemy->setPosition(_enemy->getNextPosition());
	wisp->setPosition(wisp->getNextPosition());*/
}

//�^���ʂ�0.1�ȉ��Ȃ�True
bool Player::isStop(){
	if (_vector.x < 0.1f && _vector.y < 0.1f)
	{
	return true;
	}
	return false;
}

//�E�B�X�v�ɗ͂�������
void Player::addForceToWisp(){
	_nextPosition.x += _vector.x;
	_nextPosition.y += _vector.y;
}


//�~�܂�����A�ēx�A�^�b�N�\��
void Player::stopWithSet(){
	if (isStop() && !_canFire) {
		this->setCanFire(true);
	}
}

bool Player::wispTouchBegan(){
	CCTouch *touch = _main->getBeganTouch();
	CCNode *wisp = _main->getChildByTag(kTag_wisp);

	bool ret = false;
	if (!_canFire) return false;
	if (touch) {
		_isContacted = false;
		//�^�b�`�ʒu���擾
		_touchPoint = touch->getLocation();
		//�E�B�X�v�ɐG��Ă���Ȃ玟�̏�����
		if (wisp->boundingBox().containsPoint(_touchPoint)) {
			CCLOG("OK");
			ret = true;
		}
	}
	return ret;
}

void Player::wispTouchMoved(){
	CCTouch* touch = _main->getMovedTouch();
	CCNode* wisp = _main->getChildByTag(kTag_wisp);

	if (wisp)
	{
		//CCPoint extPos = extendPos(wisp);
		//���������|�C���g�ƍ���\��
		//setChainOne(initChainOne(chain), extPos);
	}
}

void Player::wispTouchEnded(){
	CCTouch* touch = _main->getEndedTouch();
	CCNode* wisp = _main->getChildByTag(kTag_wisp);
	CCPoint endPoint = touch->getLocation();
	CCPoint force = CCPoint(_touchPoint.x - endPoint.x, _touchPoint.y - endPoint.y) * 0.5;
	this->setVector(force);
	//�V���b�g���̑����s��
	setCanFire(false);
	//if (_enemy != nullptr)
	//_enemy->removeFromParentAndCleanup(true);
}

void Player::collisionBlockWest(){
	if (gThanRadius(_nextPosition.x)) {
		_nextPosition.x = this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void Player::collisionBlockEast(){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.x, screenSize.width)) {
		_nextPosition.x = screenSize.width - this->radius();
		_vector.x *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void Player::collisionBlockNorth(){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if (lessThanRadius(_nextPosition.y, screenSize.height)) {
		_nextPosition.y = screenSize.height - this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

void Player::collisionBlockSouth(){
	if (gThanRadius(_nextPosition.y)) {
		_nextPosition.y = this->radius();
		_vector.y *= -0.8f;
		SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");
	}
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ�
bool Player::gThanRadius(float wispNextPos){
	if (wispNextPos < this->radius())
		return true;
	return false;
}

//�E�B�X�v�̔��a���ǂ𒴂�����A�Փ˂��锻���Ԃ�
bool Player::lessThanRadius(float wispNextPos, float screenwh){
	if (wispNextPos > screenwh - this->radius())
		return true;
	return false;
}

//�Փ˔���i�ʉߎ��j
void Player::onCollisionPassing(){
	CCPoint wispPosition = this->getPosition();
	Enemy *enemy = static_cast<Enemy *>(_main->getChildByTag(kTag_enemy));
	CCRect enemyRect = enemy->boundingBox();
	bool isContact = enemyRect.containsPoint(wispPosition);
	if (isContact && !_isContacted){
		CCLOG("firstHit");
		Cm::getInstance()->damageToEnemy();
		_isContacted = true;
	}
	else if (!isContact){
		_isContacted = false;
	}
}