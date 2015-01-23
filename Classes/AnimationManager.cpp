/*
* AnimationManager.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "AnimationManager.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AnimationManager::AnimationManager(){}

AnimationManager::~AnimationManager(){}

void AnimationManager::wispInitAnime(Player *wisp)
{
	//�ړ����Ȃ���t�F�[�h�C������
	CCSpawn *fadeIn = CCSpawn::create(CCFadeIn::create(1), CCMoveBy::create(1, ccp(0, wisp->radius())), NULL);
	//�c���ɗh�ꑱ����
	CCSequence *seq = CCSequence::create(CCMoveBy::create(2, ccp(0, -wisp->radius() * 0.2)), CCMoveBy::create(2, ccp(0, wisp->radius() * 0.2)), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(seq);
	wisp->runAction(fadeIn);
	wisp->runAction(repeat);
}

void AnimationManager::swingAnime(GameObject *obj)
{
	//��e���A���E�ɗh���
	CCRepeat *swing = CCRepeat::create(CCSequence::create(CCRotateTo::create(0.1, -10), CCRotateTo::create(0.1, 10), NULL), 4);
	obj->runAction(CCSequence::create(swing, CCRotateTo::create(0, 0.125), NULL));
}

void AnimationManager::wispDyingAnime(PlayerHit *wisp)
{
	//���ŃA�j���[�V�����i����Ɉړ����Ȃ���A�k�����t�F�[�h�A�E�g�j
	CCSpawn *diedSpawn = CCSpawn::create(CCScaleTo::create(1, 0, 1), CCFadeOut::create(1), CCMoveBy::create(1, ccp(0, 20)), nullptr);
	CCSequence *diedSequence = CCSequence::create(diedSpawn, nullptr);

	wisp->runAction(diedSequence);
	
	//���ŃG�t�F�N�g�i���������j
	CCSprite *vanish = CCSprite::create("wisp_dying1.png");
	vanish->setPosition(wisp->getPosition());
	MS::getInstance()->addChild(vanish, z_vanish);

	CCAnimation *vanishing = CCAnimation::create();
	vanishing->addSpriteFrameWithFileName("wisp_dying1.png");
	vanishing->addSpriteFrameWithFileName("wisp_dying2.png");
	vanishing->addSpriteFrameWithFileName("wisp_dying3.png");
	vanishing->addSpriteFrameWithFileName("wisp_dying4.png");
	vanishing->addSpriteFrameWithFileName("wisp_dying5.png");
	vanishing->setDelayPerUnit(0.2);

	CCSpawn *vanishSpawn = CCSpawn::create(CCAnimate::create(vanishing), CCFadeOut::create(1.0), nullptr);
	CCSequence *vanishSequence = CCSequence::create(vanishSpawn, CCRemoveSelf::create(), nullptr);

	vanish->runAction(vanishSequence);

	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_fire06.mp3");
}

void AnimationManager::enemyDyingAnime(EnemyHit *enemy)
{
	//�GNPC�������i����Ɉړ����Ȃ���A�k�����t�F�[�h�A�E�g�j
	CCSpawn *diedSpawn = CCSpawn::create(CCScaleTo::create(1, 0, 1), CCFadeOut::create(1), CCMoveBy::create(1, ccp(0, 20)), nullptr);
	CCSequence *diedSequence = CCSequence::create(diedSpawn, nullptr);

	enemy->runAction(diedSequence);
	
	//���ŃG�t�F�N�g(����������)
	CCSprite *vanish = CCSprite::create("dying1.png");
	vanish->setPosition(enemy->getPosition());
	MS::getInstance()->addChild(vanish, z_vanish);

	CCAnimation *vanishing = CCAnimation::create();
	vanishing->addSpriteFrameWithFileName("dying1.png");
	vanishing->addSpriteFrameWithFileName("dying2.png");
	vanishing->addSpriteFrameWithFileName("dying3.png");
	vanishing->addSpriteFrameWithFileName("dying4.png");
	vanishing->addSpriteFrameWithFileName("dying5.png");
	vanishing->setDelayPerUnit(0.2);

	CCSpawn *vanishSpawn = CCSpawn::create(CCAnimate::create(vanishing), CCFadeOut::create(1.0), nullptr);
	CCSequence *vanishSequence = CCSequence::create(vanishSpawn, CCRemoveSelf::create(), nullptr);

	vanish->runAction(vanishSequence);

	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_explosion04.mp3");
}

void AnimationManager::enemyStarAnime()
{
	MainScene *main = MS::getInstance();
	Player* wisp = static_cast<Player *>(main->getChildByTag(kTag_wisp));
	//�_���[�W���A�X�^�[�G�t�F�N�g�\��
	CCSprite *star = CCSprite::create("star1.png");
	star->setPosition(wisp->getPosition());
	main->addChild(star, z_star);

	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("star1.png");
	animation->addSpriteFrameWithFileName("star2.png");
	animation->addSpriteFrameWithFileName("star3.png");
	animation->addSpriteFrameWithFileName("star4.png");
	animation->setDelayPerUnit(0.1);

	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), CCFadeOut::create(0.45), nullptr);
	CCSequence *starSequence = CCSequence::create(spawn, CCRemoveSelf::create(), nullptr);

	star->runAction(CCScaleTo::create(0.4, 2));
	star->runAction(starSequence);
}

void AnimationManager::enemyExplodeAnime(EnemyHit *enemy)
{
	//�_���[�W���A�����G�t�F�N�g�\��
	CCSprite *ex = CCSprite::create("explode1.png");
	ex->setPosition(enemy->getPosition());
	MS::getInstance()->addChild(ex, z_explode);

	CCAnimation *explode = CCAnimation::create();
	explode->addSpriteFrameWithFileName("explode1.png");
	explode->addSpriteFrameWithFileName("explode2.png");
	explode->addSpriteFrameWithFileName("explode3.png");
	explode->addSpriteFrameWithFileName("explode4.png");
	explode->setDelayPerUnit(0.1);

	CCSpawn *exSpawn = CCSpawn::create(CCAnimate::create(explode), CCFadeOut::create(0.45), nullptr);
	CCSequence *exSequence = CCSequence::create(exSpawn, CCRemoveSelf::create(), nullptr);

	ex->runAction(exSequence);
}

void AnimationManager::enemyDamageAnime(EnemyHit *enemy)
{
	//�_���[�W���A�X�^�[�G�t�F�N�g�\��
	enemyStarAnime();
	//�_���[�W���A�GNPC���X�C���O
	swingAnime(enemy);
	//�_���[�W���A�����G�t�F�N�g�\��
	enemyExplodeAnime(enemy);
	//�_���[�W��
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_battle18.mp3");
}

void AnimationManager::boundSE()
{
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system48.mp3");
}

void AnimationManager::enemyIdleAnime(Enemy *enemy)
{
	//�c���ɗh�ꑱ����
	CCSequence *seq = CCSequence::create(CCMoveBy::create(2, ccp(0, -enemy->radius() * 0.2)), CCMoveBy::create(2, ccp(0, enemy->radius() * 0.2)), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(seq);
	enemy->runAction(repeat);
}

void AnimationManager::enemy_vamp_idleAnime(Enemy *enemy)
{
	//�c���ɗh�ꑱ����
	CCSequence *seq = CCSequence::create(CCMoveBy::create(2, ccp(0, enemy->radius() * 0.2)), CCMoveBy::create(2, ccp(0, -enemy->radius() * 0.2)), NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(seq);
	enemy->runAction(repeat);
}

CCSprite* AnimationManager::arrowAnime()
{
	//�^�b�`���̃K�C�h���ǉ�
	CCSprite *arrow = CCSprite::create("arrow1.png");
	//��󂪕ω�����A�j���[�V����
	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("arrow1.png");
	animation->addSpriteFrameWithFileName("arrow2.png");
	animation->addSpriteFrameWithFileName("arrow3.png");
	animation->addSpriteFrameWithFileName("arrow4.png");
	animation->addSpriteFrameWithFileName("arrow5.png");
	animation->setDelayPerUnit(0.3);
	//���߂̉摜�ɖ߂�
	animation->setRestoreOriginalFrame(true);
	//�_�ł��Ă���悤�Ɍ�����A�N�V����
	CCSequence *fade = CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5), NULL);
	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), fade, NULL);
	//�J��Ԃ��A�N�V����
	CCRepeatForever *repeat = CCRepeatForever::create(spawn);
	arrow->runAction(repeat);
	return arrow;
}