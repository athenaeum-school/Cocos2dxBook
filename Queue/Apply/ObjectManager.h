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
#include "AudioQueue.h"

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
	CC_SYNTHESIZE(AudioQueue *, m_pAudioQueue, AudioQueue);
	
    bool init();
    void update(float dt);
    void clean();
    bool handleBeganEvents();
	void handleMovedEvents();
	void handleEndedEvents();
	void addGameObject(GameObject* sprite);
	std::vector<GameObject*> getGameObjects();
	StateMachine* getStateMachine() { return m_pStateMachine; }

	//起動から始めのプレイ時の初期化
	void playStart();

	//プレイ回数を更新
	void addPlayCount();

	/**	背景を追加
	*	@return 背景
	*/
	cocos2d::CCSprite* initBackground();

	/**	共有HPに追加
	*	@param hp 敵NPCのHP
	*/
	void addRaidHp(int hp);

	/**	共有HPを減少
	*	@param damage プレイヤーの攻撃力
	*/
	void damageRaidHp(int damage);

	//敵NPCの総数を増加
	void addEnemyCount();

	//敵NPCの総数を減少
	void drawEnemyCount();

	//リセット処理
	void reset();

	//プレイヤーのターンがフェードインするアクション
	void fadeInState();
	
private:
    
    StateMachine* m_pStateMachine;
	EnemyFactory *m_pEnemyFactory;
	static ObjectManager* s_pInstance;
    std::vector<GameObject*> m_gameObjects;
	int m_soundCount;

	/**	AudioQueueに追加と再生をする音源を設定
	*	@param obj ゲームオブジェクト（プレイヤーと敵NPC）
	*	@return 音源ファイル名
	*/
	std::string soundEvents(GameObject *obj);

	/**	AudioQueueに追加と再生をする音源を設定（敵NPC種類に応じて）
	*	@param obj ゲームオブジェクト（敵NPC）
	*	@return 音源ファイル名
	*/
	std::string switchEnemyAttackSE(GameObject *obj);

	/**	enqueue()とplayAudio()の計2回呼び出されたか
	*	@return 真偽
	*/
	bool isGreaterThanTwo();

    ObjectManager();
    ~ObjectManager();
    
    ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
    
};

typedef ObjectManager OM;

#endif /* defined(__WillYard__ObjectManager__) */
