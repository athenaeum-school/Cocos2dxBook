/*
* AnimationManager.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__AnimationManager__
#define __WillYard__AnimationManager__

#include "cocos2d.h"
#include "Player.h"


class AnimationManager : public cocos2d::CCNode
{
public:

	CREATE_FUNC(AnimationManager);

	void wispInitAnime(Player *wisp);
	void swingAnime(GameObject *obj);
	void wispDyingAnime(Player *wisp);
	void enemyDyingAnime(Enemy *enemy);
	void enemyStarAnime();
	void enemyExplodeAnime(Enemy *enemy);
	void enemyDamageAnime(Enemy *enemy);
	void boundSE();
	void enemyIdleAnime(Enemy *enemy);
	void enemy_vamp_idleAnime(Enemy *enemy);
	

	AnimationManager();
	~AnimationManager();

private:

};

#endif /*defined(__WillYard__AnimationManager__)*/
