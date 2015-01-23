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
#include <cocos2d.h>
#include "StateMachine.h"
#include "GameObject.h"
#include "EnemyFactory.h"

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
    
	CC_SYNTHESIZE(int, m_raidHp, RaidHp);
	CC_SYNTHESIZE(int, m_enemyCount, EnemyCount);
	CC_SYNTHESIZE(int, m_playCount, PlayCount);
	CC_SYNTHESIZE(bool, m_isReady, IsReady);
	
    bool init();
    void update(float dt);
    void clean();
    bool handleBeganEvents();
	void handleMovedEvents();
	void handleEndedEvents();
	void addGameObject(GameObject* sprite);
	std::vector<GameObject*> getGameObjects();
	StateMachine* getStateMachine() { return m_pStateMachine; }
	
	void addRaidHp(int hp);
	void damageRaidHp(int damage);
	void addEnemyCount();
	void drawEnemyCount();
    void playStart();
	void addPlayCount();
	cocos2d::CCSprite* initBackground();
	void reset();
	void fadeInState();
	
private:
    
    StateMachine* m_pStateMachine;
    static ObjectManager* s_pInstance;
	EnemyFactory *m_pEnemyFactory;
    std::vector<GameObject*> m_gameObjects;
    
	void initAudio();
	
    ObjectManager();
    ~ObjectManager();
    
    ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
    
};

typedef ObjectManager OM;

#endif /* defined(__WillYard__ObjectManager__) */
