/*
* Enemy.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "Enemy.h"
#include "EnemyAttack.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ObjectManager.h"

USING_NS_CC;
using namespace CocosDenshion;

Enemy::Enemy(MainScene *main) 
: GameObject(main)
, _isAttacked(true)
, _isContacted(false)
, _isDead(false)

{
	setAtk(0);
	setHP(0);
	setMaxHP(0);
	_om = Om::getInstance();
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create(enemyType type, float xPos, float yPos){
	//エネミー生成
	Enemy * enemy = new Enemy(Main::getInstance());
	if (enemy) {
		enemy->initEnemy(type, xPos, yPos);
		enemy->autorelease();
		Main::getInstance()->addChild(enemy, z_enemy, kTag_enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(enemyType type, float xPos, float yPos)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//assert((float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y));
	this->initWithFile(fileNameInit(type).c_str());
	this->setPosition(ccp(screenSize.width * xPos, screenSize.height * yPos - 1 * this->radius()));
	this->setOpacity(0);

	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, screenSize.height * yPos - 10 * this->radius())), NULL);
	this->runAction(fadeIn);
	animationInit(type);
	
	_om->initRaidHp(this->getHP());
	_om->addEnemyCount();
	_om->addGameObjectMap("enemy", this);
	_om->addGameObject(this);
	
	return this;
}

std::string Enemy::fileNameInit(enemyType type){
	std::string fileName;

	switch (type)
	{
	case enemyType::kTag_rat1:
		fileName = "enemy1.png";
		this->setEtype(type);
		this->setHP(30);
		this->setMaxHP(30);
		this->setAtk(5);
		break;
	case enemyType::kTag_rat2:
		this->setEtype(type);
		fileName = "enemy2.png";
		this->setHP(60);
		this->setMaxHP(60);
		this->setAtk(10);
		break;
	case enemyType::kTag_vampire:
		this->setEtype(type);
		fileName = "enemy3.png";
		this->setHP(100);
		this->setMaxHP(100);
		this->setAtk(20);
		break;
	default:
		break;
	}

	return fileName;
}

void Enemy::animationInit(enemyType type){
	
	switch (type)
	{ 
		{
	case enemyType::kTag_rat1:
	case enemyType::kTag_rat2:
		_hud->getAnime()->enemyIdleAnime(this);
		break;
		}

		{
	case enemyType::kTag_vampire:
		_hud->getAnime()->enemy_vamp_idleAnime(this);
		break;
		}

		{
	default:
		break;
		}
	}

}


void Enemy::onStateEnter(){
	if (_isDead){
		return;
	}

	_wisp = static_cast<Player *>(_main->getChildByTag(kTag_wisp));
	_stateID = _om->getStateMachine()->getStates().back()->getStateID();

	if (isNormalState())
	{
		setIsContacted(false);
	}
	else if (isEnemyState())
	{
		onEnemyStateEnter();
	}
	else if (isResultState()){
		
	}
}

void Enemy::stateUpdate(float dt){
	if (_isDead){
		return;
	}

	attack();
	hitCheck();
}

void Enemy::onStateExit(){
	if (getIsDead()){
		return;
	}

	if (isEnemyState()){
		setIsContacted(false);
	}
	else if (isResultState()){
		resultExit();
	}
}


bool Enemy::isNormalState(){
	if (_stateID == "NORMAL")
	{
		return true;
	}
	return false;
}

bool Enemy::isEnemyState(){
	if (_stateID == "ENEMY")
	{
		return true;
	}
	return false;
}

bool Enemy::isResultState(){
	if (_stateID == "RESULT")
	{
		return true;
	}
	return false;
}

void Enemy::onEnemyStateEnter(){
	//敵NPCの数が減るほど、攻撃する確率が上昇する
	if (randomAttack(2.0) < 1)
	{
		setIsAttacked(false);
	}
	else if (_om->getEnemyCount() == 1)
	{
		if (randomAttack(1.3) < 1){
			setIsAttacked(false);
		}
	}
}

int Enemy::randomAttack(int value){
	int random = _om->getEnemyCount() % calcRandom(1, _om->getEnemyCount() * value);
	return random;
}


void Enemy::resultExit(){
		CCLOG("enemyOnStateExit:result");
		setHP(0);
		setIsDead(true);
		Om::getInstance()->setEnemyCount(0);
		this->runAction(CCFadeOut::create(0));
}

int Enemy::calcRandom(int min, int max)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}


void Enemy::attack(){
	if (isDeadOrAttacked() || !isEnemyState()){
		return;
	}
		EnemyAttack::create(this)->attack(this);
		setIsAttacked(true);
}

bool Enemy::isDeadOrAttacked(){
	if (_isDead || _isAttacked){
		return true;
	}
	return false;
}

void Enemy::hitCheck(){
	if (_stateID == "ENEMY"){
		return;
	}

	CCPoint enemyPosition = this->getPosition();
	CCRect wispRect = _wisp->boundingBox();
	
	bool isContact = setEnemyRect().intersectsRect(wispRect);
	
	if (isContanctWithContacted(isContact) && isDeadWithAttacking()){
		damage();
		_hud->getAnime()->enemyDamageAnime(this);
		setIsContacted(true);
	}
	else if (!isContact){
		setIsContacted(false);
	}

}


bool Enemy::isDeadWithAttacking(){
	if (!_isDead && _wisp->getIsAttacking()){
		return true;
	}
	return false;
}

bool Enemy::isContanctWithContacted(bool isContact){
	if (isContact && !_isContacted){
		return true;
	}
	return false;
}

CCRect Enemy::setEnemyRect(){
	CCRect enemyRect = CCRectMake(this->getPositionX() - (this->getContentSize().width / 4),
									this->getPositionY() - (this->getContentSize().height / 4),
									this->getContentSize().width / 2, this->getContentSize().height / 2);
	return enemyRect;
}

void Enemy::damage(){
	
	int playerAtk = _wisp->getAtk();

	_hud->damageToString(this->getPosition(), _wisp->getAtk());
	_hud->addComboCount();

	if (playerAtk <= this->_hp){
		//通常ダメージ
		normalDamage(playerAtk);
	}
	else if (playerAtk > this->_hp){
		//レイドHPとの不整合を無くすため、オーバーダメージを防ぐ処理
		overDamage();
	}
	
	CCLOG("EnemyHP : %d", _hp);

	if (_hp <= 0){
		setIsDead(true);
		died();
	}
}

//通常ダメージ
void Enemy::normalDamage(int playerAtk){
	_hp -= playerAtk;
	_om->damageRaidHp(playerAtk);
}

void Enemy::overDamage(){
	//レイドHPとの不整合を無くすため、オーバーダメージを防ぐ処理
	int margeDamage = _hp;
	_hp -= margeDamage;
	_om->damageRaidHp(margeDamage);
}

void Enemy::died(){
	if (_isDead){
		setHP(0);
		_om->drawEnemyCount();
		_hud->getAnime()->enemyDyingAnime(this);
	}
}
