/*
* ActionManager.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ActionManager__
#define __WillYard__ActionManager__

#include "cocos2d.h"
#include "Player.h"
#include "PlayerHit.h"
#include "EnemyHit.h"

class ActionManager : public cocos2d::CCNode
{
public:

	CREATE_FUNC(ActionManager);

	void wispInitAction(Player *wisp);
	void swingAction(GameObject *obj);
	void dyingAction(GameObject *obj);

	/**	���S���̉摜�t�@�C������ݒ�
	*	@param	obj �Q�[���I�u�W�F�N�g�i�v���C���[�A�GNPC�j
	*	@param	number �t�@�C�����̘A��
	*	@return	�t�@�C����+�A�Ԃ̕�����
	*/
	std::string dyingSpriteFileName(GameObject *obj, int number);

	void enemyStarAction();
	void enemyExplodeAction(EnemyHit *enemy);

	/**	�A�N�V�����̉摜�t�@�C������ݒ�i�A�j���[�V�������g�p���Ă���A�N�V�����j
	*	@param	fileName �i*"�t�@�C����%d"�j�����
	*	@param	number �t�@�C�����̘A��
	*	@return	�t�@�C����+�A�Ԃ̕�����
	*/
	std::string spriteFileName(const char& fileName, int number);

	void enemyDamageAction(EnemyHit *enemy);
	void boundSE();

	/**	�GNPC�̑ҋ@�A�N�V����
	*	@param	enemy �GNPC
	*	@param	start y���̍��W�i�͂��߂ɗh�������j
	*	@param	next y���̍��W�i���ɗh�������j
	*/
	void enemyIdleAction(Enemy *enemy, float start, float next);

	cocos2d::CCSprite* arrowAction();

	ActionManager();
	~ActionManager();

private:

	void dyingSE(GameObject *obj);
};

#endif /*defined(__WillYard__ActionManager__)*/
