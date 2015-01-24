/*
EnemyAttack* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "EnemyAttack.h"
#include "Player.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

EnemyAttack::EnemyAttack()
	:m_atkPower(0)
{}


EnemyAttack::~EnemyAttack(){}

EnemyAttack* EnemyAttack::create(Enemy *enemy)
{
	//攻撃生成
	EnemyAttack * enemyAttack = new EnemyAttack();
	if (enemyAttack) 
	{
		enemyAttack->initEnemyAttack(enemy, enemy->getPosition());
		enemyAttack->autorelease();
		MS::getInstance()->addChild(enemyAttack, z_enemyAttack, kTag_enemyAttack);
		enemyAttack->attack(enemy);
		return enemyAttack;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemyAttack);
	return NULL;
}

EnemyAttack* EnemyAttack::initEnemyAttack(Enemy *enemy, CCPoint point)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	this->initWithFile(fileNameInit(enemy->getEnemyType()).c_str());
	this->setPosition(point);
	
	return this;
}

std::string EnemyAttack::fileNameInit(enemyType type)
{
	std::string fileName;
	
	switch (type)
	{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		fileName = "attack_rat1.png";
		break;
	case enemyType::kTag_vampire:
		fileName = "attack_vampire1.png";
		break;
	default:
		break;
	}

	return fileName;
}

void EnemyAttack::attack(Enemy *enemy)
{
	//呼び出した敵NPCの攻撃力を代入
	setAtkPower(enemy->getAtkPower());
	//タイプによって、攻撃方法を変える
	switch (enemy->getEnemyType())
	{
		{
			case enemyType::kTag_rat1:
			case enemyType::kTag_rat2:
				CCAnimation *attackEffect = CCAnimation::create();
				attackEffect->addSpriteFrameWithFileName("attack_rat1.png");
				attackEffect->addSpriteFrameWithFileName("attack_rat2.png");
				attackEffect->addSpriteFrameWithFileName("attack_rat3.png");
				attackEffect->setDelayPerUnit(0.1);

				CCAnimate *attackAnime = CCAnimate::create(attackEffect);

				Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
				//ウィスプの座標へ0.7秒かけて移動
				CCMoveTo *attackMove = CCMoveTo::create(0.7f, ccp(wisp->getPositionX(), wisp->getPositionY()));
				//スプライトの切り替えと移動を同時に行なう
				CCSpawn *attackSpawn = CCSpawn::create(CCAnimate::create(attackEffect), attackMove, nullptr);
				//0.5秒後、消滅
				CCSequence *seq = CCSequence::create(attackSpawn, CCDelayTime::create(0.5), CCRemoveSelf::create(), NULL);
				this->runAction(seq);
				SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_retro18.mp3");
				break;
		}
		{
			case enemyType::kTag_vampire:
				CCAnimation *attackEffect = CCAnimation::create();
				attackEffect->addSpriteFrameWithFileName("attack_vampire1.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire2.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire3.png");
				attackEffect->addSpriteFrameWithFileName("attack_vampire4.png");
				attackEffect->setDelayPerUnit(0.2);

				CCAnimate *attackAnime = CCAnimate::create(attackEffect);

				Player *wisp = static_cast<Player *>(MS::getInstance()->getChildByTag(kTag_wisp));
				//ウィスプの座標へ1.0秒かけて移動
				CCMoveTo *attackMove = CCMoveTo::create(1.0f, ccp(wisp->getPositionX(), wisp->getPositionY()));
				//スプライトの切り替えと移動を同時に行なう
				CCSpawn *attackSpawn = CCSpawn::create(CCAnimate::create(attackEffect), attackMove,nullptr);
				//0.5秒後、消滅
				CCSequence *seq = CCSequence::create(attackSpawn, CCDelayTime::create(0.5) ,CCRemoveSelf::create(), NULL);
				this->runAction(seq);
				SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_magical23.mp3");
				break;
		}
		{
			default:
				break;
		}
	}
}

