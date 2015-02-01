/*
* ObjectManager.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "ObjectManager.h"
#include "TitleState.h"
#include "NormalState.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
//シングルトンの初期化
ObjectManager* ObjectManager::s_pInstance = 0;

ObjectManager::ObjectManager() :
m_raidHp(0),
m_enemyCount(0),
m_playCount(0),
m_soundCount(0),
m_pStateMachine(NULL),
m_isReady(false),
m_pEnemyFactory(NULL),
m_pAudioQueue(NULL)
{
	//状態マシーンの初期化
	m_pStateMachine = new StateMachine();
	//敵NPCファクトリーの初期化
	m_pEnemyFactory = EnemyFactory::create();
	//AudioQueueを初期化
	m_pAudioQueue = new AudioQueue();
}

ObjectManager::~ObjectManager(){}

bool ObjectManager::init()
{
	//初期状態を追加
	m_pStateMachine->pushState(new TitleState());
	return true;
}

void ObjectManager::update(float dt)
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		m_pAudioQueue->enqueue(soundEvents((*it)).c_str());
		m_pAudioQueue->playAudio(soundEvents((*it)).c_str());
	}
	m_pStateMachine->update(dt);
}

//GameLayerで呼び出しているインプットの処理
bool ObjectManager::handleBeganEvents()
{
	return m_pStateMachine->onBeganEvent();
}

void ObjectManager::handleMovedEvents()
{
	m_pStateMachine->onMovedEvent();
}

void ObjectManager::handleEndedEvents()
{
	m_pStateMachine->onEndedEvent();
}

std::string ObjectManager::soundEvents(GameObject *obj)
{
	std::string fileName;

		switch (obj->getTag())
		{
		case tag::kTag_wisp:
			if (obj->getIsPlayHitSE())
			{
				fileName = "se_maoudamashii_system45.mp3";
				//2回呼び出されたら（enqueue()とplayAudio()）
				if (isGreaterThanTwo())
				{
					//効果音フラグを偽に
					obj->setIsPlayHitSE(false);
				}
			}
			else if (obj->getIsPlayHitBlockSE())
			{
				fileName = "se_maoudamashii_system45.mp3";
				if (isGreaterThanTwo())
				{
					obj->setIsPlayHitBlockSE(false);
				}
			}
			else if (obj->getIsPlayDyingSE())
			{
				fileName = "se_maoudamashii_element_fire06.mp3";
				if (isGreaterThanTwo())
				{
					obj->setIsPlayDyingSE(false);
				}
			}
			break;
		case tag::kTag_enemy:
			if (obj->getIsPlayHitSE())
			{
				fileName = "se_maoudamashii_battle18.mp3";
				if (isGreaterThanTwo())
				{
					obj->setIsPlayHitSE(false);
				}
			}
			else if (obj->getIsPlayHitFastSE())
			{
				fileName = "se_maoudamashii_system48.mp3";
				if (isGreaterThanTwo())
				{
					obj->setIsPlayHitFastSE(false);
				}
			}
			else if (obj->getIsPlayDyingSE())
			{
				fileName = "se_maoudamashii_explosion04.mp3";
				if (isGreaterThanTwo())
				{
					obj->setIsPlayDyingSE(false);
				}
			}
			else if (obj->getIsPlayAttackingEnemySE())
			{
				//敵NPCの種類に応じて、効果音を判定
				fileName = switchEnemyAttackSE(obj);
			}
			break;
		default:
			break;
		}

	return fileName;
}

std::string ObjectManager::switchEnemyAttackSE(GameObject * obj)
{
	std::string fileName;
	Enemy *enemy = static_cast<Enemy *>(obj);
	//敵NPCの種類に応じて、効果音を判定
	switch (enemy->getEnemyType())
	{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		fileName = "se_maoudamashii_retro18.mp3";
		if (isGreaterThanTwo())
		{
			obj->setIsPlayAttackingEnemySE(false);
		}
		break;
	case enemyType::kTag_vampire:
		fileName = "se_maoudamashii_magical23.mp3";
		if (isGreaterThanTwo())
		{
			obj->setIsPlayAttackingEnemySE(false);
		}
		break;
	default:
		break;
	}

	return fileName;
}

bool ObjectManager::isGreaterThanTwo()
{
	//呼び出されたらカウント増加
	m_soundCount++;
	//2回呼び出されたらカウントをリセットし、真を返す
	if (m_soundCount >= 2)
	{
		m_soundCount = 0;
		return true;
	}
	return false;
}

void ObjectManager::addGameObject(GameObject* sprite)
{
	m_gameObjects.push_back(sprite);
}

std::vector<GameObject*> ObjectManager::getGameObjects()
{
	return m_gameObjects;
}

void ObjectManager::clean()
{
    cout << "cleaning ObjectManager\n";
    m_pStateMachine = 0;
    delete m_pStateMachine;
}

//起動から始めのプレイ時の初期化
void ObjectManager::playStart()
{
	//一度でもプレイしていたら以降の処理を行なわない
	if (m_playCount >= 1)
	{
		return;
	}

	//ウィスプ生成
	Player::create();
	//エネミー生成
	m_pEnemyFactory->createEnemy(kTag_rat1, 0.2, 0.5);
	m_pEnemyFactory->createEnemy(kTag_vampire, 0.5, 0.8);
	m_pEnemyFactory->createEnemy(kTag_rat2, 0.8, 0.5);
	//背景生成
	initBackground();
}

void ObjectManager::addPlayCount()
{
	//プレイ回数を更新
	m_playCount++;
}

CCSprite* ObjectManager::initBackground()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//背景画像を追加
	CCSprite * background = CCSprite::create("background0.png");
	//画面中央に配置
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	//MainSceneのインスタンスを呼び出す
	//MainSceneへ追加
	MS::getInstance()->addChild(background, z_background, kTag_background);
	return background;
}

void ObjectManager::addRaidHp(int hp)
{
	//敵NPCのHPを共有HPに追加
	m_raidHp += hp;
}

void ObjectManager::damageRaidHp(int hp)
{
	//敵NPCへのダメージを共有HPにも与える
	m_raidHp -= hp;
}

void ObjectManager::addEnemyCount()
{
	//敵NPCの総数を増加
	m_enemyCount++;
}

void ObjectManager::drawEnemyCount()
{
	//敵NPCの総数を減少
	m_enemyCount--;
}

void ObjectManager::reset()
{
	//リセット処理
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	if (m_raidHp <= 0)
	{
		wisp->resetWisp();
		
		m_pEnemyFactory->createEnemy(kTag_rat1, 0.2, 0.5);
		m_pEnemyFactory->createEnemy(kTag_vampire, 0.5, 0.8);
		m_pEnemyFactory->createEnemy(kTag_rat2, 0.7, 0.5);
		fadeInState();
	}
}

void ObjectManager::fadeInState()
{
	//プレイヤーのターンがフェードインするアクション
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//画面底からウィスプ3個分の高さへ設定
	wisp->setPositionY(wisp->getRadius() * 3);
	//フェードインのため、透明に
	wisp->setOpacity(0);
	//1秒かけて、フェードインとウィスプ1個分下に移動するアクション（引数3個目は敗北してた場合、大きさを元に戻すため）
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, wisp->getRadius() * -1.0)), CCScaleTo::create(0, 1, 1), NULL);
	wisp->runAction(fadeIn);
	
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//背景も同様にフェードインするためのアクション設定
	CCSprite *back = static_cast<CCSprite *>(MS::getInstance()->getChildByTag(kTag_background));
	back->setPosition(ccp(screenSize.width / 2, screenSize.height / 2.1));
	back->setOpacity(0);
	CCSpawn *fadeIn2 = CCSpawn::create(CCFadeIn::create(1), CCMoveTo::create(1, ccp(screenSize.width / 2, screenSize.height / 2.0)), NULL);
	back->runAction(fadeIn2);
}