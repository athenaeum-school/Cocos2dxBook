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

class EnemyTypeObject;

class Enemy : public EnemyHit 
{
public:

	/**	敵NPCを生成
	*	@param enemyTypeObject パーサーで設定をした敵NPC情報
	*	@return 敵NPC
	*/
	static Enemy* create(EnemyTypeObject *enemyTypeObject);

	CC_SYNTHESIZE(bool, m_isAttacked, IsAttacked);
	CC_SYNTHESIZE(enemyType, m_enemyType, EnemyType);
	
	void onStateEnter() override;
	void onStateExit() override;
	void stateUpdate(float dt) override;
	
	Enemy();

protected:

	/**	敵NPC初期設定
	*	@param enemyTypeObject パーサーで設定をした敵NPC情報
	*/
	void initEnemy(EnemyTypeObject *enemyTypeObject);


	/**	敵NPCの画像とステータス設定
	*	@param enemyTypeObject パーサーで設定をした敵NPC情報
	*	@return	画像ファイル名
	*/
	std::string initStatus(EnemyTypeObject *enemyTypeObject);

	//待機時のアクション
	void setIdleAction();

	
	virtual ~Enemy();

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

};

class EnemyTypeObject
{
public:

	/**	敵NPCの生成
	*	@return	敵NPC
	*/
	Enemy* createEnemy() { return Enemy::create(this); }


	/**	パーサーで敵NPCの設定を行なう
	*	@param hp 体力
	*	@param atkPower 攻撃力
	*	@param xPos 配置座標（x軸）
	*	@param yPos 配置座標(y軸)
	*	@param enemysType 敵NPCの種類	
	*	@param imageID 設定する画像ファイル
	*/
	EnemyTypeObject(int hp, int atkPower, float xPos, float yPos, int enemysType, std::string &imageID):
		m_hp(hp),
		m_atkPower(atkPower),
		m_xPos(xPos),
		m_yPos(yPos),
		m_enemyType(enemysType),
		m_imageID(imageID)
	{}

	int getHp() { return m_hp; }
	int getAtkPower(){ return m_atkPower; }
	float getXPOS(){ return m_xPos; }
	float getYPOS(){ return m_yPos; }
	int getEnemyType(){ return m_enemyType; }
	const std::string& getimageID(){ return m_imageID; }

private:

	int m_hp;
	int m_atkPower;
	float m_xPos;
	float m_yPos;
	int m_enemyType;
	std::string m_imageID;

};

#endif /*defined(__WillYard__Enemy__)*/
