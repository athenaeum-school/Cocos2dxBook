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
const float SHOT_RATE = 0.3;
//�E�B�X�v��HP
const int WISP_HP = 1;
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
	this->setHP(WISP_HP);
	this->setMaxHP(WISP_MAXHP);
	this->setAtkPower(WISP_ATK); 
}

Player::~Player(){}

Player* Player::create()
{
	Player * wisp = new Player();
	if (wisp)
	{
		wisp->initWisp();
		wisp->autorelease();
		//MainScene�̃C���X�^���X���擾���A�����ɒǉ�
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
	//x���͒����ցAy���͒ꂩ��E�B�X�v�̔��a1���󂯂����W�֔z�u
	this->setPosition(ccp(screenSize.width * 0.5, this->getRadius() * 1.0));
	//�t�F�[�h�C���̂��߁A������
	this->setOpacity(0);
	//�A�j���[�V�����̏�����
	Hud::getInstance()->getAction()->wispInitAction(this);
	//HP�o�[�̒ǉ�
	Hud::getInstance()->initHpBar(this);
	//vector�R���e�i�փE�B�X�v��ǉ�
	OM::getInstance()->addGameObject(this);

	return this;
}


void Player::onStateEnter()
{	
	//���݂̏�Ԃ�ID����
	this->setStateID();
	if (this->isNormalState())
	{
		//�v���C���[�̃^�[���J�n���̏�����
		setTouchPoint(ccp(0, 0));
		setTimer(0);
		setCanFire(true);
		//HP���x���̕\��
		Hud::getInstance()->drawHpLabel();
	}
	else if (this->isEnemyState())
	{
		
	}
	else if (this->isResultState())
	{
		
	}
}

void Player::onStateExit()
{
	if (this->isNormalState())
	{
		setIsAttacking(false);
		this->setAcceleration(ccp(0, 0));
	} 
	else if (this->isResultState())
	{
		Hud::getInstance()->initHpBar(this);
	}
}

void Player::stateUpdate(float dt)
{
	//AudioComponent������ʉ����Ăяo��
	this->m_pAudio->update(dt, this);
	//�s�k���Ă�����ȍ~�̏������s�Ȃ�Ȃ�
	if (this->m_isDead)
	{
		return;
	}
	//�E�B�X�v�ɗ͂�������
	addForceToWisp();
	//�Փ˔���
	activateCollision();
	//�U����A���̏�Ԃւ̃J�E���g�J�n
	startTimer();
}

bool Player::wispTouchBegan()
{
	bool ret = false;
	CCTouch *touch = MS::getInstance()->getBeganTouch();
	//�U���\�Ŗ�����Έȍ~�̏������s�Ȃ�Ȃ�
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
	//�^�b�`�̍��W���擾
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
	//�^�b�`�J�n���W������������W�̋��� * SHOT_RATE�̒l���v�Z���A�͂�������
	this->setAcceleration(calcForce(endPoint));
	//�����폜
	//MS::getInstance()->removeChildByTag(kTag_arrow);
	removeArrow();
	//�V���b�g���̑����s��
	setCanFire(false);
	setIsAttacking(true);
}

void Player::activateCollision()
{
	//�Փ˔���i�GNPC�̍U���j
	this->hitCheck();
	//�E�B�X�v�ƕǂ̏Փ˔���
	//��
	this->collisionBlockWest();
	//��
	this->collisionBlockEast();
	//�k
	this->collisionBlockNorth();
	//��
	this->collisionBlockSouth();
}

void Player::addPower(int power)
{
	//�p���[�A�b�v
	this->m_atkPower += power;
}

void Player::drawPower(int power)
{
	//�p���[�_�E��
	this->m_atkPower -= power;
}

void Player::addForceToWisp()
{
	//���������̉^���ʂ��E�B�X�v�ɉ�����
	this->m_nextPosition.x += this->m_acceleration.x;
	this->m_nextPosition.y += this->m_acceleration.y;
}

bool Player::isNext()
{
	bool ret = false;
	//MainScene����touchImage�̃m�[�h���L���X�g���Ď擾
	CCSprite * touchImage = static_cast<CCSprite *>(Hud::getInstance()->getChildByTag(ktag_touch));
	//�^�b�`�摜�ɐG��Ă���Ȃ玟�̏�����
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
		arrow = Hud::getInstance()->getAction()->arrowAction();
		MS::getInstance()->addChild(arrow, z_arrow, kTag_arrow);
	}
	//���̍��W�Ɗp�x�̐ݒ�
	arrowSettings(arrow, movePoint);
}

void Player::arrowSettings(CCSprite *arrow, CCPoint movePoint)
{
	arrow->setPosition(this->getPosition());
	//�^�b�`�J�n���W�ɑ΂���ړ����̃^�b�`���W�̊p�x
	//�x�N�g���im_touchPoint - movePoint�j��x���Ԃ̊p�x���ʓx�ŎZ�o
	m_angle = ((m_touchPoint - movePoint)).getAngle();
	//����͈͂̃x�N�g����Ԃ�
	CCPoint point = movePoint + m_touchPoint.rotate(CCPoint::forAngle(m_angle));
	//�ʓx����x�ւ̕ϊ�
	m_angle = CC_RADIANS_TO_DEGREES((m_touchPoint - point).getAngle() * -1.0);
	CCLOG("angle : %f", m_angle);
	//���ʂ���ɔ��f
	arrow->setRotation(m_angle);
}

void Player::removeArrow()
{
	CCSprite *arrow = static_cast<CCSprite *>(MS::getInstance()->getChildByTag(kTag_arrow));
	if (arrow)
	{
		//�K�C�h��󂪑��݂���Ȃ�AMainScene����폜
		arrow->removeFromParent();
	}
}

CCPoint Player::calcForce(CCPoint endPoint)
{
	//�^�b�`�J�n���W������������W�̋���
	float diffx = m_touchPoint.x - endPoint.x;
	float diffy = m_touchPoint.y - endPoint.y;
	//�p�x�і��Ƀu����␳�����l * SHOT_RATE�̒l���v�Z
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
	this->setHP(100);
	this->setIsDead(false);
	setCanFire(true);
	setTimer(0);
	this->setAcceleration(ccp(0, 0));
	this->setPosition(ccp(screenSize.width / 2.0, this->getRadius() * 2.0));
}