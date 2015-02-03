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

	/**	効果音の判定（AudioComponentの純粋仮想関数をoverride）
	*	@param obj ゲームオブジェクト（Playerまたは敵NPC）
	*/
	void update(float dt, GameObject *obj) override;

	/**	効果音の判定（状態で判定（AudioComponentの純粋仮想関数をoverride））
	*	@param states 各状態（タイトル、リザルト画面等）
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

	/**	攻撃効果音の判定（敵NPC）
	*	@param obj ゲームオブジェクト（敵NPC）
	*/
	void switchEnemyAttackSE(GameObject * obj);

	void enemyRatsAttackSE();
	void enemyVampireAttackSE();

};

#endif /* defined(__WillYard__ConcreteAudioComponent__) */