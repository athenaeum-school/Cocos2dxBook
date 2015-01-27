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
	
	void update(float dt, GameObject *obj);
	void titleToNormalSE();
	
	AudioComponent();
	~AudioComponent();

private:

	bool isStart();
	void initAudio();
	void playBGM();
	void collisionSE();
	void collisionFastSE();
	void enemyDamageSE();
	void wispDyingSE();
	void enemyDyingSE();
	void enemyRatsAttackSE();
	void enemyVampireAttackSE();
	void pushButtonSE();

};

#endif /* defined(__WillYard__AudioComponent__) */