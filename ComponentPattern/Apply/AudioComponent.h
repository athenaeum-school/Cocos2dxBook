/*
* AudioComponent.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__AudioComponent__
#define __WillYard__AudioComponent__

#include <cocos2d.h>
#include "SimpleAudioEngine.h"

class GameObject;

class AudioComponent : public CocosDenshion::SimpleAudioEngine
{
public:

	/**	���ʉ��̔���	
	*	@param obj �Q�[���I�u�W�F�N�g�iPlayer�܂��͓GNPC�j 
	*/
	void update(float dt, GameObject *obj);

	void titleToNormalSE();
	void playBGM();
	void pushButtonSE();
	
	AudioComponent();
	~AudioComponent();

private:

	bool isStart();
	void initAudio();
	void collisionBlockSE();
	void collisionFastSE();
	void enemyDamageSE();
	void wispDyingSE();
	void enemyDyingSE();

	/**	�U�����ʉ��̔���i�GNPC�j
	*	@param obj �Q�[���I�u�W�F�N�g�i�GNPC�j
	*/
	void switchEnemyAttackSE(GameObject * obj);

	void enemyRatsAttackSE();
	void enemyVampireAttackSE();

};

#endif /* defined(__WillYard__AudioComponent__) */