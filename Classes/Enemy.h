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
	
protected:

	/**	敵NPC初期設定
	*	@param type	enumのenemyType
	*	@param xPos	配置するx軸の座標
	*	@param yPos	配置するy軸の座標
	*	@return	生成された敵NPCを返す
	*/
	virtual Enemy* initEnemy(enemyType type, float xPos, float yPos);

	/**	敵NPCの画像とステータス設定
	*	@param type	enumのenemyType
	*	@return	画像ファイル名を返す
	*/
	virtual std::string statusInit(enemyType type) = 0;

	//待機時のアクション
	virtual void setIdleAction() = 0;

	Enemy();
	~Enemy(void);

private:
	
	/**	敵NPCの攻撃成功確率
	*	@param value 敵NPCの総数に乗算する値
	*	@return	敵NPCの総数 % (敵NPCの総数 * value)を返す
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

	////死亡しているか攻撃済みならtrue
	bool isDeadOrAttacked();
	
};

#endif /*defined(__WillYard__Enemy__)*/
