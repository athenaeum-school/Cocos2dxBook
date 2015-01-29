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

	/**	効果音の判定	
	*	@param obj ゲームオブジェクト（Playerまたは敵NPC） 
	*/
	void update(float dt, GameObject *obj);

	void titleToNormalSE();
	void pushButtonSE();
	
	AudioComponent();
	~AudioComponent();

private:

	bool isStart();
	void initAudio();
	void playBGM();
	void collisionBlockSE();
	void collisionFastSE();
	void enemyDamageSE();
	void wispDyingSE();
	void enemyDyingSE();
	void enemyRatsAttackSE();
	void enemyVampireAttackSE();

};

#endif /* defined(__WillYard__AudioComponent__) */