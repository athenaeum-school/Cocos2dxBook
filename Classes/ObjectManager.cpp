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
m_pStateMachine(NULL),
m_isReady(false),
m_pEnemyFactory(NULL)
{
	//状態マシーンの初期化
	m_pStateMachine = new StateMachine();
	//敵NPCファクトリーの初期化
	m_pEnemyFactory = EnemyFactory::create();
}

ObjectManager::~ObjectManager(){}

bool ObjectManager::init()
{
	//BGMとSEの初期化
	initAudio();
	//初期状態を追加し、状態を初期化
	m_pStateMachine->pushState(new TitleState());
	
	return true;
}

void ObjectManager::addGameObject(GameObject* sprite)
{
    m_gameObjects.push_back(sprite);
}

std::vector<GameObject*> ObjectManager::getGameObjects()
{
    return m_gameObjects;
}

void ObjectManager::update(float dt)
{
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

void ObjectManager::clean()
{
    cout << "cleaning ObjectManager\n";
    m_pStateMachine = 0;
    delete m_pStateMachine;
}

//BGMとSEの初期化
void ObjectManager::initAudio()
{
	SimpleAudioEngine *audio = SimpleAudioEngine::sharedEngine();
	audio->preloadEffect("se_maoudamashii_element_fire07.mp3");
	audio->preloadEffect("se_maoudamashii_system48.mp3");
	audio->preloadEffect("se_maoudamashii_system45.mp3");
	audio->preloadEffect("se_maoudamashii_element_fire06.mp3");
	audio->preloadEffect("se_maoudamashii_magical23.mp3");
	audio->preloadEffect("se_maoudamashii_element_wind02.mp3");
	audio->preloadEffect("se_maoudamashii_system28.mp3");
	audio->preloadEffect("se_maoudamashii_battle18.mp3");
	audio->preloadBackgroundMusic("game_maoudamashii_7_rock46.mp3");
}

//プレイスタート時の初期化
void ObjectManager::playStart()
{
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
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	//MainSceneのインスタンスを呼び出す
	//MainSceneへ追加
	MS::getInstance()->addChild(background, z_background, kTag_background);
	return background;
}

void ObjectManager::addRaidHp(int hp)
{
	//敵NPCのHPをレイドHPに追加
	m_raidHp += hp;
}

void ObjectManager::damageRaidHp(int hp)
{
	//敵NPCへのダメージをレイドHPにも与える
	m_raidHp -= hp;
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
	//通常状態がフェードインするアクション
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