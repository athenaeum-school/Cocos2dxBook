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

	/**	���ʉ��̍Đ�	
	*	@param obj �Q�[���I�u�W�F�N�g�iPlayer�܂��͓GNPC�j 
	*/
	virtual void update(float dt, GameObject *obj) = 0;

	/**	���ʉ��̍Đ��i��ԂŔ���j
	*	@param states �e��ԁi�^�C�g���A���U���g��ʓ��j
	*/
	virtual void playAudio(GameState *states) = 0;

	virtual ~AudioComponent();

protected:

	AudioComponent();

};

#endif /* defined(__WillYard__AudioComponent__) */