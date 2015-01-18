/*
* ObjectManager.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ObjectManager__
#define __WillYard__ObjectManager__


#include <vector>
#include <map>
#include <cocos2d.h>
#include "StateMachine.h"
#include "GameObject.h"
#include "EnemyFactory.h"

USING_NS_CC;

class EnemyFactory;

class ObjectManager : public cocos2d::CCLayer
{
public:
    
    static ObjectManager* getInstance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new ObjectManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
	CC_SYNTHESIZE(int, _raidHp, RaidHp);
	CC_SYNTHESIZE(int, _enemyCount, EnemyCount);
	CC_SYNTHESIZE(int, _playCount, PlayCount);
	CC_SYNTHESIZE(int, m_playerLives, PlayerLives);
	CC_SYNTHESIZE(int, m_nextLevel, NextLevel);
	CC_SYNTHESIZE(bool, m_bLevelComplete, LevelComplete);
	CC_SYNTHESIZE(bool, isReady, IsReady);
	
    bool init();
    void update(float dt);
    void clean();
    bool handleBeganEvents();
	void handleMovedEvents();
	void handleEndedEvents();
	void initRaidHp(int hp);
	void damageRaidHp(int damage);
	void addEnemyCount();
	void drawEnemyCount();

    void setGameObjectPosition(const cocos2d::CCPoint &pts);
    void setTileMap(cocos2d::CCTMXTiledMap* tileMap);
    void setGameObjectStrategy();
    
    void addGameObjectMap(std::string id, GameObject* sprite);
    void addGameObject(GameObject* sprite);
    
    std::vector<GameObject*> getGameObjects();
    std::map<std::string, GameObject*> getGameObjectMap();
    GameObject* findGameObject(std::string id);
    cocos2d::CCTMXTiledMap* getTileMap();
    
    StateMachine* getStateMachine() { return m_pStateMachine; }
    
    void setCurrentLevel(int currentLevel);
    int getCurrentLevel() { return m_currentLevel;}
    
    std::vector<std::string> getLevelFiles() { return m_levelFiles; }
    
	CCSprite* initBackground();
	void reset();
	void fadeInState();
	void playStart();
	void addPlayCount();
	
private:
    
    StateMachine* m_pStateMachine;
    static ObjectManager* s_pInstance;
	MainScene* _main;
    
	EnemyFactory *_enemyFactory;

    std::vector<GameObject*> m_gameObjects;
    std::map<std::string, GameObject*> m_gameObjectMap;
    
    cocos2d::CCTMXTiledMap *_tileMap;
    
    int m_currentLevel;

    std::vector<std::string> m_levelFiles;
    
	void initAudio();
	

    ObjectManager();
    ~ObjectManager();
    
    ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
    
    ObjectManager(const cocos2d::CCSprite*);
};

typedef ObjectManager Om;

#endif /* defined(__WillYard__ObjectManager__) */
