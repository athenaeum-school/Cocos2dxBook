/*
* ActionManager.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "ActionManager.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;
using namespace CocosDenshion;

ActionManager::ActionManager(){}

ActionManager::~ActionManager(){}

void ActionManager::wispInitAction(Player *wisp)
{
	//移動しながらフェードインする
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, wisp->getRadius())), NULL);
	//縦軸に揺れ続ける
	CCSequence *seq = CCSequence::create(CCMoveBy::create(2, ccp(0, wisp->getRadius() * -0.2)), CCMoveBy::create(2, ccp(0, wisp->getRadius() * 0.2)), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(seq);
	wisp->runAction(fadeIn);
	wisp->runAction(repeat);
}

void ActionManager::swingAction(GameObject *obj)
{
	//被弾時、左右に揺れる
	CCRepeat *swing = CCRepeat::create(CCSequence::create(CCRotateTo::create(0.1, -10), CCRotateTo::create(0.1, 10), NULL), 4);
	obj->runAction(CCSequence::create(swing, CCRotateTo::create(0, 0.125), NULL));
}

void ActionManager::dyingAction(GameObject *obj)
{
	//消滅アニメーション（上方に移動しながら、縮小しフェードアウト）
	CCSpawn *diedSpawn = CCSpawn::create(CCScaleTo::create(1, 0, 1), CCFadeOut::create(1), CCMoveBy::create(1, ccp(0, 20)), nullptr);
	CCSequence *diedSequence = CCSequence::create(diedSpawn, nullptr);

	obj->runAction(diedSequence);

	//消滅エフェクト（風が発生）
	CCSprite *vanish = CCSprite::create(dyingSpriteFileName(obj, 1).c_str());
	vanish->setPosition(obj->getPosition());
	//MainSceneのインスタンスを呼び出す
	//MainSceneへ追加
	MS::getInstance()->addChild(vanish, z_vanish);

	CCAnimation *vanishing = CCAnimation::create();
	for (int i = 1; i <= 5; i++)
	{
		//ファイル名+1~5までの画像を追加
		vanishing->addSpriteFrameWithFileName(dyingSpriteFileName(obj, i).c_str());
	}
	vanishing->setDelayPerUnit(0.2);

	CCSpawn *vanishSpawn = CCSpawn::create(CCAnimate::create(vanishing), CCFadeOut::create(1.0), nullptr);
	CCSequence *vanishSequence = CCSequence::create(vanishSpawn, CCRemoveSelf::create(), nullptr);

	vanish->runAction(vanishSequence);
}

std::string ActionManager::dyingSpriteFileName(GameObject *obj, int number)
{
	//死亡時の画像ファイル名を設定
	std::string fileName;
	CCString* editFileName;
	//ゲームオブジェクトのタグで判定
	switch (obj->getTag())
	{
	case tag::kTag_wisp:
		editFileName = CCString::createWithFormat("wisp_dying%d.png", number);
		//editFileNameをStringで取得
		fileName = editFileName->getCString();
		break;
	case tag::kTag_enemy:
		editFileName = CCString::createWithFormat("dying%d.png", number);
		fileName = editFileName->getCString();
		break;
	default:
		break;
	}

	return fileName;
}

void ActionManager::enemyStarAction()
{
	Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
	//ダメージ時、スターエフェクト表示
	CCSprite *star = CCSprite::create("star1.png");
	star->setPosition(wisp->getPosition());
	MS::getInstance()->addChild(star, z_star);

	CCAnimation *animation = CCAnimation::create();
	for (int i = 1; i <= 4; i++)
	{
		//ファイル名+1~4までの画像を追加
		animation->addSpriteFrameWithFileName(spriteFileName((*"star%d.png"), i).c_str());
	}
	animation->setDelayPerUnit(0.1);

	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), CCFadeOut::create(0.45), nullptr);
	CCSequence *starSequence = CCSequence::create(spawn, CCRemoveSelf::create(), nullptr);

	star->runAction(CCScaleTo::create(0.4, 2));
	star->runAction(starSequence);
}

void ActionManager::enemyExplodeAction(EnemyHit *enemy)
{
	//ダメージ時、爆発エフェクト表示
	CCSprite *ex = CCSprite::create("explode1.png");
	ex->setPosition(enemy->getPosition());
	MS::getInstance()->addChild(ex, z_explode);

	CCAnimation *explode = CCAnimation::create();
	for (int i = 1; i <= 4; i++)
	{
		//ファイル名+1~4までの画像を追加
		explode->addSpriteFrameWithFileName(spriteFileName((*"explode%d.png"), i).c_str());
	}
	explode->setDelayPerUnit(0.1);

	CCSpawn *exSpawn = CCSpawn::create(CCAnimate::create(explode), CCFadeOut::create(0.45), nullptr);
	CCSequence *exSequence = CCSequence::create(exSpawn, CCRemoveSelf::create(), nullptr);

	ex->runAction(exSequence);
}

std::string ActionManager::spriteFileName(const char& fileName, int number)
{
	//アクションの画像ファイル名を設定（アニメーションを使用しているアクション）
	CCString* editFileName = CCString::createWithFormat(&fileName, number);
	std::string fileNameWithNumber = editFileName->getCString();

	return fileNameWithNumber;
}

void ActionManager::enemyDamageAction(EnemyHit *enemy)
{
	//ダメージ時、スターエフェクト表示
	enemyStarAction();
	//ダメージ時、敵NPCをスイング
	swingAction(enemy);
	//ダメージ時、爆発エフェクト表示
	enemyExplodeAction(enemy);
}

void ActionManager::boundSE()
{
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system48.mp3");
}

void ActionManager::enemyIdleAction(Enemy *enemy, float start, float next)
{
	//縦軸に揺れ続ける
	CCSequence *seq = CCSequence::create(CCMoveBy::create(2, ccp(0, enemy->getRadius() * start)), CCMoveBy::create(2, ccp(0, enemy->getRadius() * next)), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(seq);
	enemy->runAction(repeat);
}

CCSprite* ActionManager::arrowAction()
{
	//タッチ時のガイド矢印追加
	CCSprite *arrow = CCSprite::create("arrow1.png");
	//矢印が変化するアニメーション
	CCAnimation *animation = CCAnimation::create();
	for (int i = 1; i <= 5; i++)
	{
		//ファイル名+1~5までの画像を追加
		animation->addSpriteFrameWithFileName(spriteFileName((*"arrow%d.png"), i).c_str());
	}
	animation->setDelayPerUnit(0.3);
	//初めの画像に戻す
	animation->setRestoreOriginalFrame(true);
	//点滅しているように見せるアクション
	CCSequence *fade = CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5), NULL);
	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), fade, NULL);
	//繰り返すアクション
	CCRepeatForever *repeat = CCRepeatForever::create(spawn);
	arrow->runAction(repeat);
	return arrow;
}