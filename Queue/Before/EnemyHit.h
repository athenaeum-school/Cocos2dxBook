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

class EnemyHit : public GameObject
{
public:

	//重複当たり判定を防ぐためのフラグ
	CC_SYNTHESIZE(bool, m_isContacted, IsContacted);

	//ダメージ処理
	void damage();
	
protected:

	//当たり判定の総合処理
	void hitCheck();

	/**	当たり判定用の処理
	*	@return 敵NPCのダメージ判定描画領域
	*/
	cocos2d::CCRect setEnemyRect();

	/**	当たり判定用の処理
	*	@param isContact_interSects	敵NPCの当たり判定にプレイヤーが触れているか
	*	@return 敵NPCに触れる、その接触までに触れていなければ真
	*/
	bool isContanctWithContacted(bool isContact_interSects);

	/**	当たり判定用の処理
	*	@return 敵NPCが生存していて、プレイヤーが攻撃中ならば真
	*/
	bool isAliveWithAttacking();
	
	/**	通常ダメージ処理
	*	@param AtkPower プレイヤーの攻撃力
	*/
	void normalDamage(int PlayerAtkPower);

	//HP以上のダメージを受けないようにする
	void overDamage();

	//死亡処理
	void died();
	
	EnemyHit();
	~EnemyHit();

};

#endif /*defined(__WillYard__EnemyHit__)*/
