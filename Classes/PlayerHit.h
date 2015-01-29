/*
* PlayerHit.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__PlayerHit__
#define __WillYard__PlayerHit__

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyAttack.h"

class PlayerHit : public GameObject 
{
protected:
	
	//敵NPCの攻撃との衝突判定
	void hitCheck();

	/**	ダメージ処理
	*	@param atkPower 敵NPCの攻撃力
	*/
	void damage(EnemyAttack *atkPower);

	//敗北処理
	void died();

	//東西南北の壁の衝突判定
	void collisionBlockWest();
	void collisionBlockEast();
	void collisionBlockNorth();
	void collisionBlockSouth();

	//衝突に関する関数を派生クラスでまとめて呼び出す純粋仮想関数
	virtual void activateCollision() = 0;

	PlayerHit();
	~PlayerHit();

private:

	/**	敵NPCの攻撃の描画領域を計算
	*	@param enemyAttack 敵NPCの攻撃
	*/
	cocos2d::CCRect enemyAtkRect(EnemyAttack *enemyAttack);

	/**	壁との衝突を判定（南、西）
	*	@param wispNextPos プレイヤーの移動先
	*/
	bool isLessThanRadius(float wispNextPos);

	/**	壁との衝突を判定（北、東）
	*	@param wispNextPos プレイヤーの移動先
	*	@param screenwh 画面サイズの横幅と高さ
	*/
	bool isGreaterThanRadius(float wispNextPos, float screenwh);
	
};

#endif /*defined(__WillYard__PlayerHit__)*/