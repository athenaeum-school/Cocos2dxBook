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
	//�t�F�[�h�C���̂��߁A������
	this->setOpacity(0);
	//�A�j���[�V�����̏�����
	_hud->getAnime()->wispInitAnime(this);

	//vector��map�R���e�i�փE�B�X�v��ǉ�
	_om->addGameObjectMap("wisp", this);
	_om->addGameObject(this);

	return this;
}


void Player::onStateEnter()
{	
	setStateID();
	if (isNormalState())
	{
		//HP���x���̕\��
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
	//�����蔻��m�F
	hitCheck();
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
	
	//�U����A���̏�Ԃւ̃J�E���g�J�n
	startTimer();
}

void Player::addPower(int power)
{
	//�p���[�A�b�v
	this->_atk += power;
}

void Player::drawPower(int power)
{
	//�p���[�_�E��
	this->_atk -= power;
}

void Player::addForceToWisp()
{
	//���������̉^���ʂ��E�B�X�v�ɉ�����
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
		//�^�b�`�ʒu���擾
		_touchPoint = touch->getLocation();
		//�E�B�X�v�ɐG��Ă���Ȃ玟�̏�����
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
	//���������W
	CCPoint endPoint = touch->getLocation();
	//�^�b�`�J�n���W������������W�̋��� * 0.5�̒l���v�Z���A�͂�������
	this->setVector(calcForce(endPoint));
	//�V���b�g���̑����s��
	setCanFire(false);
	setIsAttacking(true);
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	//�^�b�`�J�n���W������������W�̋��� * 0.5�̒l���v�Z
	return CCPoint(_touchPoint.x - endPoint.x, _touchPoint.y - endPoint.y) * 0.5;
}

void Player::startTimer()
{
	//�V���b�g��A�^�C�}�[�X�^�[�g
	if (!getCanFire()){
		++_timer;
	}
}

void Player::resetWisp()
{
	//���g���C��̍Đݒ�
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	setHP(100);
	setIsDead(false);
	setCanFire(true);
	setTimer(0);
	setVector(ccp(NULL, NULL));
	setPosition(ccp(screenSize.width * 0.5, this->radius() * 2));
}