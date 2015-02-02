/*
* EnemyVampire.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyVampire__
#define __WillYard__EnemyVampire__

#include "Enemy.h"

class EnemyVampire : public Enemy
{
public:

	/**	敵NPCを生成
	*	@param type 敵NPCの種類
	*	@param xPos 設置する座標（x軸）
	*	@param yPos 設置する座標（y軸）
	*	@return 敵NPC
	*/
	static EnemyVampire* create(float xPos, float yPos);

private:

	/**	Enemyクラスの、initEnemy(),initStatus(),setIdleAction()を呼び出し、
	*	敵NPCの設定をする純粋仮想関数
	*	@param xPos 敵NPCのx軸配置座標
	*	@param yPos 敵NPCのy軸配置座標
	*	@return 設定済みの敵NPC
	*/
	Enemy* activateSettings(float xPos, float yPos) override;

	EnemyVampire();
	~EnemyVampire();

};

#endif /* defined(__WillYard__EnemyVampire__) */