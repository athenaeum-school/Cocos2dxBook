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


USING_NS_CC;

//状態のID
const std::string NormalState::s_normalID = "NORMAL";
//高速ヒットの場合、威力が増加する値
const int ADD_POWER = 5;


NormalState::NormalState()
	:_wisp(NULL)
{
	std::cout << "NormalState::NormalState() normal state constructor\n";
}

NormalState::~NormalState() {}

void NormalState::normalToEnemy()
{
	//ウィスプを再攻撃可能、タイマーをリセットし、敵NPCのターンへ
	_wisp->setCanFire(true);
	_wisp->setTimer(0);
	_om->getStateMachine()->changeState(new EnemyState());
}

void NormalState::normalToResult()
{
	//レイドHPを0に設定し、リザルト画面へ
	CCLOG("StageClear");
	_om->setRaidHp(0);
	_om->getStateMachine()->changeState(new ResultState());
}


bool NormalState::onStateEnter() 
{
	//状態の初期化
	std::cout << "NormalState::onStateEnter()\n";
	//Readyラベル表示
	_hud->ready();
	//Aimラベル表示
	_hud->aim();
	//MainSceneからウィスプを取得
	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	//リトライ後の再設定
	_om->reset(_gObjects);
	//コンテナにゲームオブジェクトを代入
	setGameObjects();
	//ゲームオブジェクトのonStateEnter()を実行
	objectStateEnter();
		
	return true;
}


bool NormalState::onStateExit()
{
	//状態終了時（次の状態へ遷移時）の処理
	_wisp->setVector(ccp(0, 0));
	_hud->setComboCount(0);
	_hud->hide();
	objectStateExit();
	return true;
}


void NormalState::stateUpdate(float dt) 
{
	//ゲームオブジェクトのonStateUpdate()を実行
	objectStateUpdate(dt);
	//ウィスプの状態を更新（この状態内の、計算用メンバーへステータスを代入）
	setWispNextPosition(_wisp->getNextPosition());
	//ウィスプの推進力
	setWispVector(_wisp->getVector());
	//徐々に減速させる処理（運動量_wispVectorのxとyに、0.98fを掛け続ける）
	setWispVector(ccpMult(_wispVector, 0.98f));
	//衝突判定
	calcCollision();
	//最後に、ウィスプの推進力と次の目標地点に設定
	_wisp->setVector(_wispVector);
	_wisp->setNextPosition(_wispNextPosition);
	//次の目標地点へ移動
	_wisp->setPosition(_wisp->getNextPosition());
	//次の状態へ遷移
	switchState();
}



void NormalState::switchState()
{
	if (isGreaterThanCount(250))
	{
		//ウィスプのタイマーが250を超えたら敵NPCのターンへ
		normalToEnemy();
	}
	else if (isLessThanZero() && isGreaterThanCount(200))
	{
		//レイドHPが0かつ、ウィスプのタイマーが200を超えたらリザルト状態へ
		normalToResult();
	}
}

bool NormalState::isLessThanZero()
{
	int raidHp = _om->getRaidHp();
	if (raidHp <= 0)
	{
		return true;
	}
	return false;
}

bool NormalState::isGreaterThanCount(int count)
{
	int timer = _wisp->getTimer();
	//ウィスプのタイマーがカウント以上ならTrue
	if (timer > count)
	{
		return true;
	}
	return false;
}

bool NormalState::onTouchBeganEvent()
{
	//isReadyがFalseなら抜ける
	if (!_om->getIsReady())
	{
		return false;
	}
	CCLOG("hp:wisp%d", _wisp->getHP());
	CCLOG("raidHp : %d", _om->getRaidHp());
	CCLOG("playCount : %d", _om->getPlayCount());
	return _wisp->wispTouchBegan();
}

void NormalState::onTouchMovedEvent()
{
	_wisp->wispTouchMoved();
}

void NormalState::onTouchEndedEvent()
{
	_wisp->wispTouchEnded();
}


void NormalState::calcCollision()
{
	//敵NPCの設定
	for (std::vector<GameObject*>::iterator it = _gObjects.begin(); it != _gObjects.end(); ++it)
	{
		if ((*it)->getTag() == kTag_enemy)
		{
			//kTag_enemy付きのゲームオブジェクトを取り出し、Enemy型へキャスト
			Enemy *enemy = static_cast<Enemy *>((*it));

			setEnemyNextPosition(enemy->getNextPosition());
			setEnemyVector(enemy->getVector());
			//ウィスプの次のx、y座標と、敵NPCの現在のx、y座標の距離を算出
			float diffx = CalcDiff(_wispNextPosition.x, enemy->getPositionX());
			float diffy = CalcDiff(_wispNextPosition.y, enemy->getPositionY());
			//ｘ、ｙの距離を２乗し、足した値を代入
			float distOne = CalcSum(pow(diffx, 2), pow(diffy, 2));
			//ウィスプの現在のx、y座標と、敵NPCの次のx、y座標の距離を２乗し、足した値を代入
			float distTwo = CalcSum(pow(_wisp->getPositionX() - _enemyNextPosition.x, 2), pow(_wisp->getPositionY() - _enemyNextPosition.y, 2));
			
			//衝突判定(高速時)
			onCollisionFast(distOne, distTwo, calcVector(enemy), enemy);
		}
	}
}


//衝突（高速時）の処理
void NormalState::onCollisionFast(float distOne, float distTwo, float radius, Enemy *enemy)
{
	//敵NPCが死亡しているなら、判定を行なわない
	if (enemy->getIsDead())
	{
		return;
	}

	//衝突判定（敵NPCとの距離が、（ウィスプ半径+敵NPC半径）の2乗以下なら衝突）
	if (isLessThanRadius(distOne, radius) || isLessThanRadius(distTwo, radius))
	{
		CCLOG("secondHit");

		//ウィスプの次の座標とエネミーの現在座標との距離を取得
		float diffx = CalcDiff(_wispNextPosition.x, enemy->getPositionX());
		float diffy = CalcDiff(_wispNextPosition.y, enemy->getPositionY());
		//ウィスプと敵NPCの衝突時の運動量を計算
		float mag_wisp = CalcSum(pow(_wispVector.x, 2), pow(_wispVector.y, 2));
		float mag_enemy = CalcSum(pow(_enemyVector.x, 2), pow(_enemyVector.y, 2));

		//バウンドする方向への運動量
		float force = sqrt(mag_wisp + mag_enemy);
		//逆正接を算出（衝突位置から、跳ね返る角度を計算）
		float angle = atan2(diffy, diffx);
		//angleの角度へ力を加える
		_wispVector.x = force * cos(angle);
		_wispVector.y = (force * sin(angle));
		//ウィスプの移動座標を算出
		_wispNextPosition.x = _enemyNextPosition.x + (enemy->radius() + _wisp->radius() + force) * cos(angle);
		_wispNextPosition.y = _enemyNextPosition.y + (enemy->radius() + _wisp->radius() + force) * sin(angle);
		//ボーナスダメージを攻撃力に追加
		_wisp->addPower(ADD_POWER);
		_hud->getAnime()->enemyDamageAnime(enemy);
		enemy->damage();
		//ダメージ後、攻撃力を戻す
		_wisp->drawPower(ADD_POWER);
		_hud->getAnime()->boundSE();
	}

}

bool NormalState::isLessThanRadius(float dist, float radius)
{
	if (dist <= radius)
	{
		return true;
	}
	return false;
}

float NormalState::CalcDiff(float nextPos, float getPos)
{
	//距離を算出
	float diff = nextPos - getPos;
	return diff;
}

float NormalState::CalcSum(float powOne, float powTwo)
{
	//和を算出
	float dist = powOne + powTwo;
	return dist;
}


//衝突判定(高速ヒット時)
float NormalState::calcVector(Enemy *enemy)
{
	//ウィスプの速度が10以下なら抜ける
	if (_wispVector.x < 10, _wispVector.y < 10)
	{
		return 0;
	}
	//敵NPC、ウィスプの半径を足し、2乗した値を返す
	float squared_radius = pow(enemy->radius() + _wisp->radius(), 2);
	return squared_radius;
}