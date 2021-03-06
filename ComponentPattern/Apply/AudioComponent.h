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
class GameState;

class AudioComponent : public CocosDenshion::SimpleAudioEngine
{
public:

	/**	効果音の再生	
	*	@param obj ゲームオブジェクト（Playerまたは敵NPC） 
	*/
	virtual void update(float dt, GameObject *obj) = 0;

	/**	効果音の再生（状態で判定）
	*	@param states 各状態（タイトル、リザルト画面等）
	*/
	virtual void playAudio(GameState *states) = 0;

	virtual ~AudioComponent();

protected:

	AudioComponent();

};

#endif /* defined(__WillYard__AudioComponent__) */