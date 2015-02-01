/*
* NormalState.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "NormalState.h"
#include "EnemyState.h"
#include "ResultState.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "HudLayer.h"

USING_NS_CC;

//状態のID
const std::string NormalState::s_normalID = "NORMAL";
//高速ヒットの場合、威力が増加する値
const int ADD_POWER = 5;
//敵ターンへのカウント
const float TO_ENEMY = 250;
//リザルト状態へのカウント
const float TO_RESULT = 200;
//高速衝突判定の基準速度
const float HIT_SPEED = 10;

NormalState::NormalState() :
m_pWisp(NULL)
{
	std::cout << "NormalState::NormalState() normal state constructor\n";
}

NormalState::~NormalState(){}

void NormalState::normalToEnemy()
{
	//OnjectManagerのインスタンスを呼び出し、
	//敵NPCのターンへ
	OM::getInstance()->getStateMachine()->changeState(new EnemyState());
}

void NormalState::normalToResult()
{
	//レイドHPを0に設定し、リザルト画面へ
	CCLOG("StageClear");
	OM::getInstance()->setRaidHp(0);
	OM::getInstance()->getStateMachine()->changeState(new ResultState());
}


bool NormalState::onStateEnter() 
{
	//状態の初期化
	std::cout << "NormalState::onStateEnter()\n";
	//HudLayerのインスタンスを呼び出し、
	//Readyラベル表示
	Hud::getInstance()->readyImage();
	//Aimラベル表示
	Hud::getInstance()->aimImage();
	//MainSceneからウィスプを取得
	m_pWisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//リトライ後の再設定
	OM::getInstance()->reset();
	//コンテナにゲームオブジェクトを代入
	this->setGameObjects();
	//ゲームオブジェクトのonStateEnter()を実行
	this->objectStateEnter();
		
	return true;
}


bool NormalState::onStateExit()
{
	//ヒットカウントをリセットし、非表示に
	Hud::getInstance()->setHitCount(0);
	Hud::getInstance()->hideHitCountLabel();
	//ゲームオブジェクトのonStateExit()を実行
	this->objectStateExit();
	return true;
}


void NormalState::stateUpdate(float dt) 
{
	//ゲームオブジェクトのonStateUpdate()を実行
	this->objectStateUpdate(dt);
	//ウィスプの状態を更新（この状態内の、計算用メンバーへステータスを代入）
	setWispNextPosition(m_pWisp->getNextPosition());
	//ウィスプの推進力
	setWispVector(m_pWisp->getAcceleration());
	//徐々に減速させる処理（運動量_wispVectorのxとyに、0.98fを掛け続ける）
	setWispVector(ccpMult(m_wispVector, 0.98f));
	//衝突判定
	calcCollision();
	//最後に、ウィスプの推進力と次の目標地点に設定
	m_pWisp->setAcceleration(m_wispVector);
	m_pWisp->setNextPosition(m_wispNextPosition);
	//次の目標地点へ移動
	m_pWisp->setPosition(m_pWisp->getNextPosition());
	//次の状態へ遷移
	switchState();
}

bool NormalState::onTouchBeganEvent()
{
	//Readyの表示が終わるまでは操作不可に
	if (OM::getInstance()->getIsReady())
	{
		return false;
	}
	CCLOG("hp:wisp%d", m_pWisp->getHP());
	CCLOG("raidHp : %d", OM::getInstance()->getRaidHp());
	CCLOG("playCount : %d", OM::getInstance()->getPlayCount());
	//ウィスプのインスタンスからタッチ操作を呼び出す
	return m_pWisp->wispTouchBegan();
}

void NormalState::onTouchMovedEvent()
{
	m_pWisp->wispTouchMoved();
}

void NormalState::onTouchEndedEvent()
{
	m_pWisp->wispTouchEnded();
}

void NormalState::switchState()
{
	if (isGreaterThanCount(TO_ENEMY))
	{
		//ウィスプのタイマーが250を超えたら敵NPCのターンへ
		normalToEnemy();
	}
	else if (isRaidHpLessThanZero() && isGreaterThanCount(TO_RESULT))
	{
		//共有HPが0かつ、ウィスプのタイマーが200を超えたらリザルト状態へ
		normalToResult();
	}
}

bool NormalState::isRaidHpLessThanZero()
{
	//ObjectManagerの共有HPが0以下なら真
	int raidHp = OM::getInstance()->getRaidHp();
	if (raidHp <= 0)
	{
		return true;
	}
	return false;
}

bool NormalState::isGreaterThanCount(int count)
{
	int timer = m_pWisp->getTimer();
	//ウィスプのタイマーがカウント以上なら真
	if (timer > count)
	{
		return true;
	}
	return false;
}

void NormalState::calcCollision()
{
	//敵NPCの設定
	for (std::vector<GameObject*>::iterator it = this->m_gameObjects.begin(); it != this->m_gameObjects.end(); ++it)
	{
		if ((*it)->getTag() == kTag_enemy)
		{
			//kTag_enemy付きのゲームオブジェクトを取り出し、Enemy型へキャスト
			Enemy *enemy = static_cast<Enemy *>((*it));
			
			setEnemyNextPosition(enemy->getNextPosition());
			//ウィスプの次のx、y座標と、敵NPCの現在のx、y座標の距離を算出
			float diffx = calcDiff(m_wispNextPosition.x, enemy->getPositionX());
			float diffy = calcDiff(m_wispNextPosition.y, enemy->getPositionY());
			//ｘ、ｙの距離を２乗し、足した値を代入
			float distOne = calcSum(pow(diffx, 2), pow(diffy, 2));
			//ウィスプの現在のx、y座標と、敵NPCの次のx、y座標の距離を２乗し、足した値を代入
			float distTwo = calcSum(pow(m_pWisp->getPositionX() - m_enemyNextPosition.x, 2), pow(m_pWisp->getPositionY() - m_enemyNextPosition.y, 2));
			
			//衝突判定(高速時)
			onCollisionFast(distOne, distTwo, calcVector(enemy), enemy);
		}
	}
}


//衝突（高速時）の処理
void NormalState::onCollisionFast(float distOne, float distTwo, float radius, Enemy *enemy)
{
	//敵NPCが死亡しているなら、衝突判定を行なわない
	if (enemy->getIsDead())
	{
		return;
	}

	//衝突判定（敵NPCとの距離が、（ウィスプ半径+敵NPC半径）の2乗以下なら衝突）
	if (isLessThanRadius(distOne, radius) || isLessThanRadius(distTwo, radius))
	{
		CCLOG("secondHit");

		//ウィスプの次の座標とエネミーの現在座標との距離を取得
		float diffx = calcDiff(m_wispNextPosition.x, enemy->getPositionX());
		float diffy = calcDiff(m_wispNextPosition.y, enemy->getPositionY());
		//ウィスプの衝突時の運動量を計算
		float mag_wisp = calcSum(pow(m_wispVector.x, 2), pow(m_wispVector.y, 2));
		
		//バウンドする方向への運動量
		float force = sqrt(mag_wisp);
		//逆正接を算出（衝突位置から、跳ね返る角度を計算）
		float angle = atan2(diffy, diffx);
		//angleの角度へ力を加える
		m_wispVector.x = force * cos(angle);
		m_wispVector.y = (force * sin(angle));
		//ウィスプの移動座標を算出
		m_wispNextPosition.x = m_enemyNextPosition.x + (enemy->getRadius() + m_pWisp->getRadius() + force) * cos(angle);
		m_wispNextPosition.y = m_enemyNextPosition.y + (enemy->getRadius() + m_pWisp->getRadius() + force) * sin(angle);
		//ボーナスダメージを攻撃力に追加
		m_pWisp->addPower(ADD_POWER);
		Hud::getInstance()->getAction()->enemyDamageAction(enemy);
		enemy->damage();
		//高速衝突効果音を鳴らすフラグを真に
		enemy->setIsPlayHitFastSE(true);
		//ダメージ後、攻撃力を戻す
		m_pWisp->drawPower(ADD_POWER);
	}

}

bool NormalState::isLessThanRadius(float dist, float radius)
{
	//距離が半径以下なら真
	if (dist <= radius)
	{
		return true;
	}
	return false;
}

float NormalState::calcDiff(float nextPos, float getPos)
{
	//距離を算出
	float diff = nextPos - getPos;
	return diff;
}

float NormalState::calcSum(float powOne, float powTwo)
{
	//和を算出
	float dist = powOne + powTwo;
	return dist;
}


//衝突判定(高速ヒット時)
float NormalState::calcVector(Enemy *enemy)
{
	//ウィスプの速度がHIT_SPEED以下なら抜ける
	if (m_wispVector.x < HIT_SPEED, m_wispVector.y < HIT_SPEED)
	{
		return 0;
	}
	//敵NPC、ウィスプの半径を足し、2乗した値を返す（衝突する領域）
	float squared_radius = pow(enemy->getRadius() + m_pWisp->getRadius(), 2.0);
	return squared_radius;
}