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
	//HP�o�[�̒ǉ�
	_hud->initHpbar(this);

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
		setTouchPoint(ccp(0, 0));
		setTimer(0);
		setCanFire(true);
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
	bool ret = false;
	CCTouch *touch = _main->getBeganTouch();
	if (!_canFire)
	{
		return ret;
	}
	
	if (touch)
	{
		//�^�b�`�ʒu���擾
		setTouchPoint(touch->getLocation());
		//�^�b�`�摜�ɐG��Ă���Ȃ玟�̏�����
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
		//�K�C�h����ǉ�
		createArrow(movePoint);
	}
}

void Player::wispTouchEnded()
{
	CCTouch* touch = _main->getEndedTouch();
	//���������W
	CCPoint endPoint = touch->getLocation();
	//�^�b�`�J�n���W������������W�̋��� * 0.5�̒l���v�Z���A�͂�������
	this->setVector(calcForce(endPoint));
	//�����폜
	_main->removeChildByTag(kTag_arrow);
	//�V���b�g���̑����s��
	setCanFire(false);
	setIsAttacking(true);
}

bool Player::toTheNext()
{
	bool ret = false;
	//�^�b�`�摜�ɐG��Ă���Ȃ玟�̏�����
	CCSprite * touchImage = static_cast<CCSprite *>(_hud->getChildByTag(ktag_touch));
	if (touchImage && touchImage->boundingBox().containsPoint(_touchPoint))
	{
		//�^�b�`�摜���폜
		touchImage->removeFromParent();
		ret = true;
	}

	return ret;
}

void Player::createArrow(CCPoint movePoint)
{
	CCSprite *arrow = static_cast<CCSprite *>(_main->getChildByTag(kTag_arrow));
	//���݂��Ȃ���΁A����ǉ��i�P�������Ȃ����߂̏����j
	if (!arrow)
	{
		arrow = _hud->getAnime()->arrowAnime();
		_main->addChild(arrow, z_arrow, kTag_arrow);
	}
	//���̍��W�Ɗp�x�̐ݒ�
	arrowSettings(arrow, movePoint);
}

void Player::arrowSettings(CCSprite *arrow, CCPoint movePoint)
{
	arrow->setPosition(this->getPosition());
	//�^�b�`�J�n���W�ɑ΂���ړ����̃^�b�`���W�̊p�x
	float angle = ((_touchPoint - movePoint)).getAngle();
	CCPoint pos = movePoint + _touchPoint.rotate(CCPoint::forAngle(angle));
	angle = CC_RADIANS_TO_DEGREES((_touchPoint - pos).getAngle() * -1);
	//���ʂ���ɔ��f
	arrow->setRotation(angle);
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	float diffx = _touchPoint.x - endPoint.x;
	float diffy = _touchPoint.y - endPoint.y;
	//�^�b�`�J�n���W������������W�̋��� * 0.5�̒l���v�Z
	return ccp(diffx, diffy) * 0.5;
}

void Player::startTimer()
{
	//�V���b�g��A�^�C�}�[�X�^�[�g
	if (!_canFire)
	{
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