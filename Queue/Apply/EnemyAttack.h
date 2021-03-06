/*
* EnemyAttack.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyAttack__
#define __WillYard__EnemyAttack__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyAttack : public cocos2d::CCSprite 
{
public:

	CC_SYNTHESIZE(int, m_atkPower, AtkPower);
	
	/**	敵NPCの攻撃を生成
	*	@param enemy 攻撃を行なうNPC
	*	@return 生成された攻撃
	*/
	static EnemyAttack* create(Enemy *enemy);

	/**	敵NPCの攻撃
	*	@param enemy 攻撃を行なうNPC
	*/
	void attack(Enemy *enemy);

	EnemyAttack();
	~EnemyAttack();

private:

	/**	攻撃の画像ファイルを指定
	*	@param type 敵NPCの種類
	*	@return	種別に応じた攻撃の画像ファイル名
	*/
	std::string initFileName(enemyType type);

	/**	攻撃の位置とファイル情報を設定
	*	@param enemy 攻撃を行なう敵NPC
	*	@param point 敵NPCの座標（攻撃発生座標）
	*	@return	設定された攻撃
	*/
	EnemyAttack* initEnemyAttack(Enemy *enemy, cocos2d::CCPoint point);

};

#endif /*defined(__WillYard__EnemyAttack__)*/
