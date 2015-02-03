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
	//一度以上プレイしていたら以降の処理を行なわない
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
			//効果音フラグを偽に
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
			//敵NPCの種類に応じて、効果音を判定
			switchEnemyAttackSE(obj);
		}
		break;
	default:
		break;
	}
}

void ConcreteAudioComponent::playAudio(GameState *states)
{
	//状態のIDを取得
	std::string stateID = states->getStateID();
	//状態IDに応じて、音源を再生
	if (stateID == "TITLE")
	{
		TitleState *title = static_cast<TitleState *>(states);
		//BGMフラグが真ならば、BGMを再生
		if (title->getIsPlayBGM())
		{
			playBGM();
			return;
		}
		//効果音を再生
		titleToNormalSE();
	}
	else if (stateID == "RESULT")
	{
		pushButtonSE();
	}
}

bool ConcreteAudioComponent::isStart()
{
	//ObjectManagerのインスタンスを呼び出し、プレイ回数を取得
	int playCount = OM::getInstance()->getPlayCount();
	//一度以上プレイしていたら偽を返す
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
	//敵NPCの種類に応じて、効果音を判定
	switch (enemy->getEnemyType())
	{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		enemyRatsAttackSE();
		//効果音フラグを偽に
		enemy->setIsAttackingEnemySE(false);
		break;
	case enemyType::kTag_vampire:
		enemyVampireAttackSE();
		//効果音フラグを偽に
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