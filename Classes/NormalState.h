/*
* NormalState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__NormalState__
#define __WillYard__NormalState__

#include "GameState.h"
#include <cocos2d.h>
#include "Player.h"
#include "Enemy.h"

class NormalState : public GameState
{
public:
	//計算用メンバー
	CC_SYNTHESIZE(cocos2d::CCPoint, m_wispVector, WispVector);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_wispNextPosition, WispNextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_enemyNextPosition, EnemyNextPosition);

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

    std::string getStateID() override { return s_normalID; }
	
    NormalState();
    ~NormalState();

private:
   
	Player *m_pWisp;
    static const std::string s_normalID;
    
	void normalToEnemy();
	void normalToResult();

	//次の状態を判断する
    void switchState();

	/**	ObjectManagerのレイドHPが0以下か確認
	*	@return	真偽
	*/
	bool isRaidHpLessThanZero();

	/**	ウィスプのタイマーが0以上か確認
	*	@return	真偽
	*/
	bool isGreaterThanCount(int count);

	//高速衝突判定のための計算
	void calcCollision();

	/**	ウィスプのタイマーが0以上か確認
	*	@param distOne ウィスプの次のx、y座標と、敵NPCの現在のx、y座標の距離をそれぞれ２乗し、そのxとyの和
	*	@param distTwo ウィスプの現在のx、y座標と、敵NPCの次のx、y座標の距離をそれぞれ２乗し、そのxとyの和
	*	@param enemy 敵NPC 
	*/
	void onCollisionFast(float distOne, float distTwo, float radius, Enemy *enemy);


	bool isLessThanRadius(float dist, float radius);
	float CalcDiff(float nextPos, float getPos);
	float CalcSum(float powOne, float powTwo);
	float calcVector(Enemy *enemy);
	
};


#endif /* defined(__WillYard__NormalState__) */
