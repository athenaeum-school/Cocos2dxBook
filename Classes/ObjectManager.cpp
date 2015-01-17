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

ObjectManager* ObjectManager::s_pInstance = 0;

ObjectManager::ObjectManager()
:_raidHp(0)
,_enemyCount(0)
,_playCount(0)
,m_pStateMachine(0)
,m_playerLives(3)
,m_bLevelComplete(false)
,isReady(false)
, _main(Main::getInstance())
{
	SimpleAudioEngine::sharedEngine()->preloadEffect("se_maoudamashii_element_fire07.mp3");
	//状態マシーンの初期化
    m_pStateMachine = new StateMachine();
    m_currentLevel = 1;
}

ObjectManager::~ObjectManager(){}

bool ObjectManager::init()
{
	CCLOG("OMInit");
	//BGMとSEの初期化
	initAudio();
	//初期状態を追加し、状態を初期化
	m_pStateMachine->pushState(new TitleState());

	return true;
}

//BGMとSEの初期化
void ObjectManager::initAudio()
{
	SimpleAudioEngine *audio = SimpleAudioEngine::sharedEngine();
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
	if (_playCount >= 1)
	{
		return;
	}

	//ウィスプ生成
	Player::create();
	//エネミー生成
	Enemy::create(kTag_rat1, 0.2, 0.5);
	Enemy::create(kTag_vampire, 0.5, 0.8);
	Enemy::create(kTag_rat2, 0.7, 0.5);
	//背景生成
	initBackground();
}

void ObjectManager::addPlayCount()
{
	_playCount++;
}

void ObjectManager::setGameObjectPosition(const cocos2d::CCPoint &pts)
{
    for (std::vector<GameObject*>::iterator it = m_gameObjects.begin() ; it != m_gameObjects.end(); ++it)
        (*it)->setPosition(pts);
}

void ObjectManager::setTileMap(cocos2d::CCTMXTiledMap* tileMap)
{
    this->_tileMap = tileMap;
}

cocos2d::CCTMXTiledMap* ObjectManager::getTileMap()
{
    return this->_tileMap;
}

void ObjectManager::setGameObjectStrategy()
{
    //for (std::vector<GameObject*>::iterator it = m_gameObjects.begin() ; it != m_gameObjects.end(); ++it)
       // (*it)->setStrategy();
}

void ObjectManager::addGameObject(GameObject* sprite)
{
    m_gameObjects.push_back(sprite);
}

void ObjectManager::addGameObjectMap(const std::string id, GameObject* sprite)
{
    m_gameObjectMap.insert(pair<std::string, GameObject*>(id, sprite));
}

std::vector<GameObject*> ObjectManager::getGameObjects()
{
    return m_gameObjects;
}

GameObject* ObjectManager::findGameObject(std::string id)
{
    std::map<std::string, GameObject*>::iterator it = m_gameObjectMap.find(id);
    if(it != m_gameObjectMap.end()){
        return it->second;
    } else {
        return 0;
    }
}

void ObjectManager::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_pStateMachine->changeState(new NormalState());
    m_bLevelComplete = false;
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
    //m_pStateMachine->clean();
    m_pStateMachine = 0;
    delete m_pStateMachine;

}

CCSprite* ObjectManager::initBackground()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//背景画像を追加
	CCSprite * background = CCSprite::create("background0.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_main->addChild(background, z_background, kTag_background);
	return background;
}

void ObjectManager::initRaidHp(int hp)
{
	//敵NPCのHPをレイドHPに追加
	_raidHp += hp;
}

void ObjectManager::damageRaidHp(int hp)
{
	//敵NPCへのダメージをレイドHPにも与える
	_raidHp -= hp;
}

void ObjectManager::reset()
{
	//リセット処理
	Player *wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	if (_raidHp <= 0)
	{
		wisp->resetWisp();
		
		Enemy::create(kTag_rat1, 0.2, 0.5);
		Enemy::create(kTag_vampire, 0.5, 0.8);
		Enemy::create(kTag_rat2, 0.7, 0.5);
		fadeInState();
	}
}

void ObjectManager::fadeInState()
{
	//通常状態がフェードインするアクション
	Player *wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	wisp->setPositionY(wisp->radius() * 3);
	wisp->setOpacity(0);
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, -wisp->radius())), CCScaleTo::create(0,1,1), NULL);
	wisp->runAction(fadeIn);
	
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *back = static_cast<CCSprite *>(_main->getChildByTag(kTag_background));
	back->setPosition(ccp(screenSize.width / 2, screenSize.height / 2.1));
	back->setOpacity(0);
	CCSpawn *fadeIn2 = CCSpawn::create(CCFadeIn::create(1), CCMoveTo::create(1, ccp(screenSize.width / 2, screenSize.height / 2.0)), NULL);
	back->runAction(fadeIn2);

}

void ObjectManager::addEnemyCount()
{
	//敵NPCの総数を増加
	this->_enemyCount++;
}

void ObjectManager::drawEnemyCount()
{
	//敵NPCの総数を減少
	this->_enemyCount--;
}