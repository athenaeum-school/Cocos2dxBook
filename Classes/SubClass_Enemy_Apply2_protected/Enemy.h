/*
* Enemy.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__Enemy__
#define __WillYard__Enemy__

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyHit.h"

//敵NPCの種別
enum enemyType
{
	kTag_rat1 = 1,
	kTag_rat2,
	kTag_vampire,
	kTag_enemyLength,

};

class Enemy : public EnemyHit 
{
public:

	CC_SYNTHESIZE(bool, m_isAttacked, IsAttacked);
	CC_SYNTHESIZE(enemyType, m_enemyType, EnemyType);
	
	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
	/**	敵NPC初期設定
	*	@param xPos	配置するx軸の座標
	*	@param yPos	配置するy軸の座標
	*	@return	生成された敵NPC
	*/
	//virtual Enemy* initEnemy(float xPos, float yPos);

	/**	敵NPCの画像とステータス設定
	*	@param type	敵NPCの種類
	*	@param hp	敵NPCのHP
	*	@param maxHp 敵NPCの最大HP
	*	@param atkPower	敵NPCの攻撃力
	*/
	//void initStatus(enemyType type, int hp, int maxHp, int atkPower);

	/**	敵NPCの待機アクション（y軸に繰り返す）
	*	@param start 始めに揺れる方向
	*	@param next	次に揺れる方向
	*/
	//void setIdleAction(float start, float next);

protected:

	/**	派生クラス内で、initEnemy(),initStatus(),setIdleAction()を呼び出す純粋仮想関数
	*	@param enemy 生成された敵NPC
	*	@param xPos	敵NPCのx軸配置座標
	*	@param yPos 敵NPCのy軸配置座標
	*/
	virtual Enemy* activateSettings(Enemy *enemy, float xPos, float yPos) = 0;
	
	/**	敵NPC初期設定
	*	@param xPos	配置するx軸の座標
	*	@param yPos	配置するy軸の座標
	*	@return	生成された敵NPC
	*/
	virtual Enemy* initEnemy(float xPos, float yPos);

	/**	敵NPCの画像とステータス設定
	*	@param type	敵NPCの種類
	*	@param hp	敵NPCのHP
	*	@param maxHp 敵NPCの最大HP
	*	@param atkPower	敵NPCの攻撃力
	*/
	void initStatus(enemyType type, int hp, int maxHp, int atkPower);

	/**	敵NPCの待機アクション（y軸に繰り返す）
	*	@param start 始めに揺れる方向
	*	@param next	次に揺れる方向
	*/
	void setIdleAction(float start, float next);

	Enemy();
	~Enemy(void);

private:
	
	/**	敵NPCの攻撃成功確率
	*	@param value 敵NPCの総数に乗算する値
	*	@return	敵NPCの総数 % (敵NPCの総数 * value)
	*/
	int randomAttack(int value);

	/**	min~maxの値を整数で返す
	*	@param min 最小値
	*	@param max 最大値
	*	@return	min~max間の乱数
	*/
	int calcRandom(int min, int max);

	//攻撃を行なう
	void attack();
	//EnemyHitクラスのHitCheck()を呼び出す仮想関数をoverride
	void activateHitCheck() override;
	/**	死亡しているか攻撃済みか
	*	@return	真偽
	*/
	bool isDeadOrAttacked();
	
};

#endif /*defined(__WillYard__Enemy__)*/
