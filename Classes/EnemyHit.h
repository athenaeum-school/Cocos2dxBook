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
	* 重複当たり判定を防ぐためのフラグ
	*/
	CC_SYNTHESIZE(bool, m_isContacted, IsContacted);

	void damage();

protected:

	Player *m_pWisp;

	void hitCheck();
	cocos2d::CCRect setEnemyRect();

	/**	当たり判定
	*	@param isContact_interSects	自身の当たり判定にプレイヤーが触れているか
	*	@return	敵NPCに触れる、その接触までに触れていなければ真
	*/
	bool isContanctWithContacted(bool isContact_interSects);

	/**	当たり判定
	*	@return	敵NPCが生存していて、プレイヤーが攻撃中ならば真
	*/
	bool isAliveWithAttacking();
	
	void normalDamage(int playerAtk);
	void overDamage();
	void died();
	
	EnemyHit();
	~EnemyHit();

};

#endif /*defined(__WillYard__EnemyHit__)*/
