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
#include "NormalState.h"
//#include "ApproachState.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

ObjectManager* ObjectManager::s_pInstance = 0;

ObjectManager::ObjectManager():
_raidHp(0),
m_pStateMachine(0),
m_playerLives(3),
m_bLevelComplete(false)
{
	//状態マシーンの初期化
    m_pStateMachine = new StateMachine();
    m_currentLevel = 1;
	_main = MainScene::getInstance();
}

ObjectManager::~ObjectManager()
{

}

bool ObjectManager::init()
{
	//BGMとSEの初期化
	initAudio();
	
	//ウィスプ生成
	Player::create(100);
	//エネミー生成
	Enemy::create("enemy1.png", 10, 0.2, 0.5);
	Enemy::create("enemy3.png", 10, 0.5, 0.8);
	Enemy::create("enemy2.png", 10, 0.7, 0.5);
	//背景生成
	initBackground();

	//初期状態を追加し、状態を初期化
	m_pStateMachine->pushState(new NormalState());

	return true;
}

//BGMとSEの初期化
void ObjectManager::initAudio(){
	SimpleAudioEngine *audio = SimpleAudioEngine::sharedEngine();
	audio->preloadEffect("se_maoudamashii_system48.mp3");
	audio->preloadEffect("se_maoudamashii_system45.mp3");
	audio->preloadBackgroundMusic("game_maoudamashii_7_rock46.mp3");
	audio->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
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

void ObjectManager::handleMovedEvents(){
	m_pStateMachine->onMovedEvent();
}

void ObjectManager::handleEndedEvents(){
	m_pStateMachine->onEndedEvent();
}

void ObjectManager::clean()
{
    cout << "cleaning ObjectManager\n";
    //m_pStateMachine->clean();
    m_pStateMachine = 0;
    delete m_pStateMachine;

}

CCSprite* ObjectManager::initBackground(){
	//背景の設定
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//背景画像
	CCSprite * background = CCSprite::create("background0.png");
	background->setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0));
	_main->addChild(background, z_background, kTag_background);
	return background;
}

void ObjectManager::initRaidHp(int hp){
	_raidHp += hp;
}

void ObjectManager::damageRaidHp(int hp){
	_raidHp -= hp;
}