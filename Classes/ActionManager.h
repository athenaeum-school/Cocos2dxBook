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

	void wispInitAction(Player *wisp);
	void swingAction(GameObject *obj);
	void dyingAction(GameObject *obj);

	/**	死亡時の画像ファイル名を設定
	*	@param	obj ゲームオブジェクト（プレイヤー、敵NPC）
	*	@param	number ファイル名の連番
	*	@return	ファイル名+連番の文字列
	*/
	std::string dyingSpriteFileName(GameObject *obj, int number);

	void enemyStarAction();
	void enemyExplodeAction(EnemyHit *enemy);

	/**	アクションの画像ファイル名を設定（アニメーションを使用しているアクション）
	*	@param	fileName （*"ファイル名%d"）を入力
	*	@param	number ファイル名の連番
	*	@return	ファイル名+連番の文字列
	*/
	std::string spriteFileName(const char& fileName, int number);

	void enemyDamageAction(EnemyHit *enemy);
	void boundSE();

	/**	敵NPCの待機アクション
	*	@param	enemy 敵NPC
	*	@param	start y軸の座標（はじめに揺れる方向）
	*	@param	next y軸の座標（次に揺れる方向）
	*/
	void enemyIdleAction(Enemy *enemy, float start, float next);

	cocos2d::CCSprite* arrowAction();

	ActionManager();
	~ActionManager();

private:

	void dyingSE(GameObject *obj);
};

#endif /*defined(__WillYard__ActionManager__)*/
