/*
* EnemyHit.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyHit__
#define __WillYard__EnemyHit__

#include "cocos2d.h"
#include "GameObject.h"

class Player;

class EnemyHit : public GameObject
{
public:
	/**
	* @param m_isContacted
	*d•¡“–‚½‚è”»’è‚ğ–h‚®‚½‚ß‚Ìƒtƒ‰ƒO
	*/
	CC_SYNTHESIZE(bool, m_isContacted, IsContacted);

	void damage();

protected:

	Player *m_pWisp;

	void hitCheck();
	cocos2d::CCRect setEnemyRect();
	bool isDeadWithAttacking();
	bool isContanctWithContacted(bool isContact);
	void normalDamage(int playerAtk);
	void overDamage();
	void died();
	
	EnemyHit();
	~EnemyHit();

};

#endif /*defined(__WillYard__EnemyHit__)*/
