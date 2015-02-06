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
#include "ObjectParser.h"

class ObjectManager : public cocos2d::CCNode
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

	//�N������n�߂̃v���C���̏�����
	void playStart();

	//�v���C�񐔂��X�V
	void addPlayCount();

	/**	�w�i��ǉ�
	*	@return �w�i
	*/
	cocos2d::CCSprite* initBackground();

	/**	���LHP�ɒǉ�
	*	@param hp �GNPC��HP
	*/
	void addRaidHp(int hp);

	/**	���LHP������
	*	@param damage �v���C���[�̍U����
	*/
	void damageRaidHp(int damage);

	//�GNPC�̑����𑝉�
	void addEnemyCount();

	//�GNPC�̑���������
	void drawEnemyCount();

	//���Z�b�g����
	void reset();

	//�v���C���[�̃^�[�����t�F�[�h�C������A�N�V����
	void fadeInState();
	
private:
    
    StateMachine* m_pStateMachine;
	ConfigParser *m_pConfigParser;
	static ObjectManager* s_pInstance;
    std::vector<GameObject*> m_gameObjects;
	
	//����������
	void initAudio();

    ObjectManager();
    ~ObjectManager();
    
    ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
    
};

typedef ObjectManager OM;

#endif /* defined(__WillYard__ObjectManager__) */
