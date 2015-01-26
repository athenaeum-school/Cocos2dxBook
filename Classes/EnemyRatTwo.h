/*
* EnemyRatTwo.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyRatTwo__
#define __WillYard__EnemyRatTwo__

#include "Enemy.h"

class EnemyRatTwo : public Enemy
{
public:

	/**	敵NPCを生成
	*	@param type 敵NPCの種類
	*	@param xPos 設置する座標（x軸）
	*	@param yPos 設置する座標（y軸）
	*	@return	敵NPC
	*/
	static EnemyRatTwo* create(enemyType type, float xPos, float yPos);

private:

	/**	敵NPCの画像とステータス設定
	*	@param type 敵NPCの種類
	*	@return	画像ファイル名
	*/
	std::string statusInit(enemyType type) override;

	//待機時のアクション
	void setIdleAction() override;

	EnemyRatTwo();
	~EnemyRatTwo();

};

#endif /* defined(__WillYard__EnemyRatTwo__) */