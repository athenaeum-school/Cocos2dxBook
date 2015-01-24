/*
EnemyAttack* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyAttack.h"
#include "Player.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

EnemyAttack::EnemyAttack()
	:m_atkPower(0)
{}


EnemyAttack::~EnemyAttack(){}

EnemyAttack* EnemyAttack::create(Enemy *enemy)
{
	//�U������
	EnemyAttack * enemyAttack = new EnemyAttack();
	if (enemyAttack) 
	{
		enemyAttack->initEnemyAttack(enemy, enemy->getPosition());
		enemyAttack->autorelease();
		MS::getInstance()->addChild(enemyAttack, z_enemyAttack, kTag_enemyAttack);
		enemyAttack->attack(enemy);
		return enemyAttack;
	}
	//autorelease���g�p���Ă��邽�߁Adelete�̑���Ɏg�p�A���������J��
	//���x���������Ȃ��悤�ɃK�[�h��������
	CC_SAFE_DELETE(enemyAttack);
	return NULL;
}

EnemyAttack* EnemyAttack::initEnemyAttack(Enemy *enemy, CCPoint point)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	this->initWithFile(fileNameInit(enemy->getEnemyType()).c_str());
	this->setPosition(point);
	
	return this;
}

std::string EnemyAttack::fileNameInit(enemyType type)
{
	std::string fileName;
	
	switch (type)
	{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		fileName = "attack_rat1.png";
		break;
	case enemyType::kTag_vampire:
		fileName = "attack_vampire1.png";
		break;
	default:
		break;
	}

	return fileName;
}

void EnemyAttack::attack(Enemy *enemy)
{
	//�Ăяo�����GNPC�̍U���͂���
	setAtkPower(enemy->getAtkPower());
	//�^�C�v�ɂ���āA�U�����@��ς���
	switch (enemy->getEnemyType())
	{
		{
			case enemyType::kTag_rat1:
			case enemyType::kTag_rat2:
				CCAnimation *attackEffect = CCAnimation::create();
				attackEffect->addSpriteFrameWithFileName("attack_rat1.png");
				attackEffect->addSpriteFrameWithFileName("attack_rat2.png");
				attackEffect->addSpriteFrameWithFileName("attack_rat3.png");
				attackEffect->setDelayPerUnit(0.1);

				CCAnimate *attackAnime = CCAnimate::create(attackEffect);

				Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
				//�E�B�X�v�̍��W��0.7�b�����Ĉړ�
				CCMoveTo *attackMove = CCMoveTo::create(0.7f, ccp(wisp->getPositionX(), wisp->getPositionY()));
				//�X�v���C�g�̐؂�ւ��ƈړ��𓯎��ɍs�Ȃ�
				CCSpawn *attackSpawn = CCSpawn::create(CCAnimate::create(attackEffect), attackMove, nullptr);
				//0.5�b��A����
				CCSequence *seq = CCSequence::create(attackSpawn, CCDelayTime::create(0.5), CCRemoveSelf::create(), NULL);
				this->runAction(seq);
				SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_retro18.mp3");
				break;
		}
		{
			case enemyType::kTag_vampire:
				CCAnimation *attackEffect = CCAnimation::create();
				attackEffect->addSpriteFrameWithFileName("attack_vampire1.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire2.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire3.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire4.png");
				attackEffect->setDelayPerUnit(0.2);

				CCAnimate *attackAnime = CCAnimate::create(attackEffect);

				Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
				//�E�B�X�v�̍��W��1.0�b�����Ĉړ�
				CCMoveTo *attackMove = CCMoveTo::create(1.0f, ccp(wisp->getPositionX(), wisp->getPositionY()));
				//�X�v���C�g�̐؂�ւ��ƈړ��𓯎��ɍs�Ȃ�
				CCSpawn *attackSpawn = CCSpawn::create(CCAnimate::create(attackEffect), attackMove,nullptr);
				//0.5�b��A����
				CCSequence *seq = CCSequence::create(attackSpawn, CCDelayTime::create(0.5) ,CCRemoveSelf::create(), NULL);
				this->runAction(seq);
				SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_magical23.mp3");
				break;
		}
		{
			default:
				break;
		}
	}
}

