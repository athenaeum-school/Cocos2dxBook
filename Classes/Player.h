/*
* Player.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__Player__
#define __WillYard__Player__

#include "cocos2d.h"
#include "PlayerHit.h"

class Player : public PlayerHit
{
public:
	
	CC_SYNTHESIZE(bool, m_canFire, CanFire);
	CC_SYNTHESIZE(bool, m_isAttacking, IsAttacking);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_touchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_force, Force);
	CC_SYNTHESIZE(int, m_timer, Timer);
	
	static Player* create();

	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();

	/**	攻撃力が増える
	*	@param power プレイヤーの攻撃力
	*/
	void addPower(int power);

	/**	攻撃力を減らす
	*	@param power プレイヤーの攻撃力
	*/
	void drawPower(int power);

	//ショット後、タイマースタート
	void startTimer();

	//リトライ後の再設定
	void resetWisp();

private:

	float m_angle;

	//プレイヤーの初期設定
	Player* initWisp();

	//放した時の運動量をプレイヤーに加える
	void addForceToWisp();

	/**	
	*	@return タッチイメージに触れていたら次の処理へ
	*/
	bool isNext();

	/**	ガイド矢印を作成
	*	@param movePoint タッチ中の座標
	*/
	void createArrow(cocos2d::CCPoint movePoint);

	/**	ガイド矢印の角度を計算
	*	@param arrow 矢印オブジェクト
	*	@param movePoint タッチ中の座標
	*/
	void arrowSettings(cocos2d::CCSprite *arrow, cocos2d::CCPoint movePoint);

	/**	プレイヤーに加速度を加える（角度の補正も行なう）
	*	@param endPoint 放した時のタッチ座標
	*	@return 加える力
	*/
	cocos2d::CCPoint calcForce(cocos2d::CCPoint endPoint);
	
	Player();
	~Player();

};

#endif /*defined(__WillYard__Player__)*/
