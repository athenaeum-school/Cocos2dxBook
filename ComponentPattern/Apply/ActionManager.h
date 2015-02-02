/*
* ActionManager.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ActionManager__
#define __WillYard__ActionManager__

#include "cocos2d.h"
#include "Player.h"
#include "PlayerHit.h"
#include "EnemyHit.h"

class ActionManager : public cocos2d::CCNode
{
public:

	CREATE_FUNC(ActionManager);

	/**	アクションを設定
	*	@param wisp プレイヤー
	*/
	void wispInitAction(Player *wisp);

	/**	被弾時のアクションを設定
	*	@param obj ゲームオブジェクト（プレイヤー、敵NPC）
	*/
	void swingAction(GameObject *obj);

	/**	死亡時のアクションを設定
	*	@param obj ゲームオブジェクト（プレイヤー、敵NPC）
	*/
	void dyingAction(GameObject *obj);

	/**	死亡時の画像ファイル名を設定
	*	@param obj ゲームオブジェクト（プレイヤー、敵NPC）
	*	@param number ファイル名の連番
	*	@return ファイル名+連番の文字列
	*/
	std::string dyingSpriteFileName(GameObject *obj, int number);

	//敵NPCの被弾時のアクションを設定（星を表示）
	void enemyStarAction();

	/**	敵NPC被弾時のアクションを設定（爆発を表示）
	*	@param enemyHit 敵NPC
	*/
	void enemyExplodeAction(EnemyHit *enemy);

	/**	アクションの画像ファイル名を設定（アニメーションを使用しているアクション）
	*	@param fileName "ファイル名%d"を入力
	*	@param number ファイル名の連番
	*	@return ファイル名+連番の文字列
	*/
	std::string spriteFileName(const char *fileName, int number);

	/**	敵NPC被弾時のアクションを設定
	*	@param enemyHit 敵NPC
	*/
	void enemyDamageAction(EnemyHit *enemy);

	//高速衝突時の効果音
	void hitFastSE();

	/**	敵NPCの待機アクション
	*	@param enemy 敵NPC
	*	@param start y軸の座標（はじめに揺れる方向）
	*	@param next y軸の座標（次に揺れる方向）
	*/
	void enemyIdleAction(Enemy *enemy, float start, float next);

	/**	ガイド矢印を追加
	*	@return	ガイド矢印
	*/
	cocos2d::CCSprite* arrowAction();

	ActionManager();
	~ActionManager();

private:

	/**	死亡時の効果音
	*	@param obj ゲームオブジェクト（プレイヤー、敵NPC）
	*/
	void dyingSE(GameObject *obj);

};

#endif /*defined(__WillYard__ActionManager__)*/