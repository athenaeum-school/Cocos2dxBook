/*
* ConcreteAudioComponent.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "ConcreteAudioComponent.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "TitleState.h"
#include "Player.h"

ConcreteAudioComponent::ConcreteAudioComponent()
{
	initAudio();
}

ConcreteAudioComponent::~ConcreteAudioComponent(){}

void ConcreteAudioComponent::initAudio()
{
	//��x�ȏ�v���C���Ă�����ȍ~�̏������s�Ȃ�Ȃ�
	if (!isStart())
	{
		return;
	}
	this->preloadEffect("se_maoudamashii_element_fire07.mp3");
	this->preloadEffect("se_maoudamashii_system48.mp3");
	this->preloadEffect("se_maoudamashii_system45.mp3");
	this->preloadEffect("se_maoudamashii_element_fire06.mp3");
	this->preloadEffect("se_maoudamashii_explosion04.mp3");
	this->preloadEffect("se_maoudamashii_magical23.mp3");
	this->preloadEffect("se_maoudamashii_system28.mp3");
	this->preloadEffect("se_maoudamashii_retro18.mp3");
	this->preloadEffect("se_maoudamashii_battle18.mp3");
	this->preloadBackgroundMusic("game_maoudamashii_7_rock46.mp3");
}

void ConcreteAudioComponent::update(float dt, GameObject *obj)
{
	switch (obj->getTag())
	{
	case tag::kTag_wisp:
		if (obj->getIsPlayHitSE())
		{
			collisionBlockSE();
			//���ʉ��t���O���U��
			obj->setIsPlayHitSE(false);
		}
		else if (obj->getIsPlayHitBlockSE())
		{
			collisionBlockSE();
			obj->setIsPlayHitBlockSE(false);
		}
		else if (obj->getIsPlayDyingSE())
		{
			wispDyingSE();
			obj->setIsPlayDyingSE(false);
		}
		break;
	case tag::kTag_enemy:
		if (obj->getIsPlayHitSE())
		{
			enemyDamageSE();
			obj->setIsPlayHitSE(false);
		}
		else if (obj->getIsHitFastSE())
		{
			collisionFastSE();
			obj->setIsHitFastSE(false);
		}
		else if (obj->getIsPlayDyingSE())
		{
			enemyDyingSE();
			obj->setIsPlayDyingSE(false);
		}
		else if (obj->getIsAttackingEnemySE())
		{
			//�GNPC�̎�ނɉ����āA���ʉ��𔻒�
			switchEnemyAttackSE(obj);
		}
		break;
	default:
		break;
	}
}

void ConcreteAudioComponent::playAudio(GameState *states)
{
	//��Ԃ�ID���擾
	std::string stateID = states->getStateID();
	//���ID�ɉ����āA�������Đ�
	if (stateID == "TITLE")
	{
		TitleState *title = static_cast<TitleState *>(states);
		//BGM�t���O���^�Ȃ�΁ABGM���Đ�
		if (title->getIsPlayBGM())
		{
			playBGM();
			return;
		}
		//���ʉ����Đ�
		titleToNormalSE();
	}
	else if (stateID == "RESULT")
	{
		pushButtonSE();
	}
}

bool ConcreteAudioComponent::isStart()
{
	//ObjectManager�̃C���X�^���X���Ăяo���A�v���C�񐔂��擾
	int playCount = OM::getInstance()->getPlayCount();
	//��x�ȏ�v���C���Ă�����U��Ԃ�
	if (playCount > 0)
	{
		return false;
	}
	return true;
}

void ConcreteAudioComponent::titleToNormalSE()
{
	this->playEffect("se_maoudamashii_element_fire07.mp3");
}

void ConcreteAudioComponent::playBGM()
{
	this->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
}

void ConcreteAudioComponent::collisionBlockSE()
{
	this->playEffect("se_maoudamashii_system45.mp3");
}

void ConcreteAudioComponent::collisionFastSE()
{
	this->playEffect("se_maoudamashii_system48.mp3");
}

void ConcreteAudioComponent::enemyDamageSE()
{
	this->playEffect("se_maoudamashii_battle18.mp3");
}

void ConcreteAudioComponent::wispDyingSE()
{
	this->playEffect("se_maoudamashii_element_fire06.mp3");
}

void ConcreteAudioComponent::enemyDyingSE()
{
	this->playEffect("se_maoudamashii_explosion04.mp3");
}

void ConcreteAudioComponent::switchEnemyAttackSE(GameObject * obj)
{
	Enemy *enemy = static_cast<Enemy *>(obj);
	//�GNPC�̎�ނɉ����āA���ʉ��𔻒�
	switch (enemy->getEnemyType())
	{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		enemyRatsAttackSE();
		//���ʉ��t���O���U��
		enemy->setIsAttackingEnemySE(false);
		break;
	case enemyType::kTag_vampire:
		enemyVampireAttackSE();
		//���ʉ��t���O���U��
		enemy->setIsAttackingEnemySE(false);
		break;
	default:
		break;
	}
}

void ConcreteAudioComponent::enemyRatsAttackSE()
{
	this->playEffect("se_maoudamashii_retro18.mp3");
}

void ConcreteAudioComponent::enemyVampireAttackSE()
{
	this->playEffect("se_maoudamashii_magical23.mp3");
}

void ConcreteAudioComponent::pushButtonSE()
{
	this->playEffect("se_maoudamashii_system28.mp3");
}