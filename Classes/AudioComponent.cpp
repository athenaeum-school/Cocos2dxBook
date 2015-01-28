/*
* AudioComponent.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "AudioComponent.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "TitleState.h"
#include "Player.h"

USING_NS_CC;
using namespace CocosDenshion;

AudioComponent::AudioComponent()
{
	initAudio();
}

AudioComponent::~AudioComponent(){}

void AudioComponent::update(float dt, GameObject *obj)
{
	switch (obj->getTag())
	{
	case tag::kTag_wisp:
		if (obj->getIsPlayHitSE())
		{
			collisionSE();
			obj->setIsPlayHitSE(false);
		}
		else if (obj->getIsPlayHitBlockSE())
		{
			collisionSE();
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
		break;
	default:
		break;
	}
}

void AudioComponent::initAudio()
{
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

bool AudioComponent::isStart()
{
	int playCount = OM::getInstance()->getPlayCount();
	
	if (playCount > 0)
	{
		return false;
	}
	return true;
}

void AudioComponent::titleToNormalSE()
{
	this->playEffect("se_maoudamashii_element_fire07.mp3");
}

void AudioComponent::playBGM()
{
	this->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
}

void AudioComponent::collisionSE()
{
	this->playEffect("se_maoudamashii_system45.mp3");
}

void AudioComponent::collisionFastSE()
{
	this->playEffect("se_maoudamashii_system48.mp3");
}

void AudioComponent::enemyDamageSE()
{
	this->playEffect("se_maoudamashii_battle18.mp3");
}

void AudioComponent::wispDyingSE()
{
	this->playEffect("se_maoudamashii_element_fire06.mp3");
}

void AudioComponent::enemyDyingSE()
{
	this->playEffect("se_maoudamashii_explosion04.mp3");
}

void AudioComponent::enemyRatsAttackSE()
{
	this->playEffect("se_maoudamashii_retro18.mp3");
}

void AudioComponent::enemyVampireAttackSE()
{
	this->playEffect("se_maoudamashii_magical23.mp3");
}

void AudioComponent::pushButtonSE()
{
	AudioComponent *audio = new AudioComponent();
	audio->playEffect("se_maoudamashii_system28.mp3");
	delete audio;
	audio = NULL;
}