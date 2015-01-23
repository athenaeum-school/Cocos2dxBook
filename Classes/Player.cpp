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
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;
//�V���b�g���̉^���ʔ{��
const float SHOT_RATE = 0.4;
//�E�B�X�v��HP
const int WISP_HP = 100;
//�ő�HP
const int WISP_MAXHP = 100;
//�U����
const int WISP_ATK = 10;

Player::Player():
m_canFire(true),
m_isAttacking(false),
m_touchPoint(ccp(0, 0)),
m_timer(0),
m_angle(0)
{
	setHP(WISP_HP);
	setMaxHP(WISP_MAXHP);
	setAtk(WISP_ATK); 
}

Player::~Player(){}

Player* Player::create()
{
	Player * wisp = new Player();
	if (wisp)
	{
		wisp->initWisp();
		wisp->autorelease();
		MS::getInstance()->addChild(wisp, z_wisp, kTag_wisp);
		return wisp;
	}
	CC_SAFE_DELETE(wisp);
	return NULL;
}

Player* Player::initWisp()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	this->initWithFile("wisp_1.png");
	this->setPosition(ccp(screenSize.width * 0.5, this->radius() * 1.0));
	//�t�F�[�h�C���̂��߁A������
	this->setOpacity(0);
	//�A�j���[�V�����̏�����
	Hud::getInstance()->getAnime()->wispInitAnime(this);
	//HP�o�[�̒ǉ�
	Hud::getInstance()->initHpbar(this);

	//vector��map�R���e�i�փE�B�X�v��ǉ�
	OM::getInstance()->addGameObject(this);

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
		Hud::getInstance()->drawHpLabel();
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
		Hud::getInstance()->initHpbar(this);
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

bool Player::wispTouchBegan()
{
	bool ret = false;
	CCTouch *touch = MS::getInstance()->getBeganTouch();
	if (!m_canFire)
	{
		return ret;
	}
	
	if (touch)
	{
		//�^�b�`�ʒu���擾
		setTouchPoint(touch->getLocation());
		//�^�b�`�摜�ɐG��Ă���Ȃ玟�̏�����
		ret = isNext();
	}

	return ret;
}

void Player::wispTouchMoved()
{
	CCTouch* touch = MS::getInstance()->getMovedTouch();
	CCPoint movePoint = touch->getLocation();
	if (touch)
	{
		//�K�C�h����ǉ�
		createArrow(movePoint);
	}
}

void Player::wispTouchEnded()
{
	CCTouch* touch = MS::getInstance()->getEndedTouch();
	//���������W
	CCPoint endPoint = touch->getLocation();
	//�^�b�`�J�n���W������������W�̋��� * 0.5�̒l���v�Z���A�͂�������
	this->setVector(calcForce(endPoint));
	//�����폜
	MS::getInstance()->removeChildByTag(kTag_arrow);
	//�V���b�g���̑����s��
	setCanFire(false);
	setIsAttacking(true);
}

void Player::addPower(int power)
{
	//�p���[�A�b�v
	this->m_atk += power;
}

void Player::drawPower(int power)
{
	//�p���[�_�E��
	this->m_atk -= power;
}

void Player::addForceToWisp()
{
	//���������̉^���ʂ��E�B�X�v�ɉ�����
	m_nextPosition.x += m_vector.x;
	m_nextPosition.y += m_vector.y;
}

bool Player::isNext()
{
	bool ret = false;
	//�^�b�`�摜�ɐG��Ă���Ȃ玟�̏�����
	CCSprite * touchImage = static_cast<CCSprite *>(Hud::getInstance()->getChildByTag(ktag_touch));
	if (touchImage && touchImage->boundingBox().containsPoint(m_touchPoint))
	{
		//�^�b�`�摜���폜
		touchImage->removeFromParent();
		ret = true;
	}

	return ret;
}

void Player::createArrow(CCPoint movePoint)
{
	CCSprite *arrow = static_cast<CCSprite *>(MS::getInstance()->getChildByTag(kTag_arrow));
	//���݂��Ȃ���΁A����ǉ��i�P�������Ȃ����߂̏����j
	if (!arrow)
	{
		arrow = Hud::getInstance()->getAnime()->arrowAnime();
		MS::getInstance()->addChild(arrow, z_arrow, kTag_arrow);
	}
	//���̍��W�Ɗp�x�̐ݒ�
	arrowSettings(arrow, movePoint);
}

void Player::arrowSettings(CCSprite *arrow, CCPoint movePoint)
{
	arrow->setPosition(this->getPosition());
	//�^�b�`�J�n���W�ɑ΂���ړ����̃^�b�`���W�̊p�x
	m_angle = ((m_touchPoint - movePoint)).getAngle();
	CCPoint point = movePoint + m_touchPoint.rotate(CCPoint::forAngle(m_angle));
	m_angle = CC_RADIANS_TO_DEGREES((m_touchPoint - point).getAngle() * -1.0);
	CCLOG("angle : %f", m_angle);
	//���ʂ���ɔ��f
	arrow->setRotation(m_angle);
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	//�^�b�`�J�n���W������������W�̋��� * 0.5�̒l���v�Z
	float diffx = m_touchPoint.x - endPoint.x;
	float diffy = m_touchPoint.y - endPoint.y;
	//�p�x�і��Ƀu����␳
	if (m_angle > -10.0 && m_angle < 10.0)
	{
		CCLOG("top");
		return ccp(diffx - 30, diffy) * SHOT_RATE;
	}
	else if (m_angle > 160)
	{
		CCLOG("bottomRight");
		return ccp(diffx + 45, diffy + 15) * SHOT_RATE;
	}
	else if (m_angle < -160)
	{
		CCLOG("bottomLeft");
		return ccp(diffx + 60, diffy - 45) * SHOT_RATE;
	}
	else if (m_angle < -91.0)
	{
		CCLOG("mAngle%f", m_angle);
		CCLOG("leftlow");
		return ccp(diffx + 30, diffy - 30) * SHOT_RATE;
	}
	else if (m_angle > 91.0 && m_angle < 180)
	{
		CCLOG("mAngle%f", m_angle);
		CCLOG("rightlow");
		return ccp(diffx + 15, diffy + 15) * SHOT_RATE;
	}
	return ccp(diffx - 15, diffy) * SHOT_RATE;
}

void Player::startTimer()
{
	//�V���b�g��A�^�C�}�[�X�^�[�g
	if (!m_canFire)
	{
		++m_timer;
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
	setVector(ccp(0, 0));
	setPosition(ccp(screenSize.width / 2.0, this->radius() * 2.0));
}