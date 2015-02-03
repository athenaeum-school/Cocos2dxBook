/*
* ConcreteAudioComponent.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ConcreteAudioComponent__
#define __WillYard__ConcreteAudioComponent__

#include <cocos2d.h>
#include "AudioComponent.h"

class ConcreteAudioComponent : public AudioComponent
{
public:

	/**	���ʉ��̔���iAudioComponent�̏������z�֐���override�j
	*	@param obj �Q�[���I�u�W�F�N�g�iPlayer�܂��͓GNPC�j
	*/
	void update(float dt, GameObject *obj) override;

	/**	���ʉ��̔���i��ԂŔ���iAudioComponent�̏������z�֐���override�j�j
	*	@param states �e��ԁi�^�C�g���A���U���g��ʓ��j
	*/
	void playAudio(GameState *states) override;

	ConcreteAudioComponent();
	~ConcreteAudioComponent();

private:

	bool isStart();
	void initAudio();
	void collisionBlockSE();
	void collisionFastSE();
	void enemyDamageSE();
	void wispDyingSE();
	void enemyDyingSE();
	void titleToNormalSE();
	void playBGM();
	void pushButtonSE();

	/**	�U�����ʉ��̔���i�GNPC�j
	*	@param obj �Q�[���I�u�W�F�N�g�i�GNPC�j
	*/
	void switchEnemyAttackSE(GameObject * obj);

	void enemyRatsAttackSE();
	void enemyVampireAttackSE();

};

#endif /* defined(__WillYard__ConcreteAudioComponent__) */