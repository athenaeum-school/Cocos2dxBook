/*
* EnemyAttack.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__EnemyAttack__
#define __WillYard__EnemyAttack__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyAttack : public cocos2d::CCSprite 
{
public:

	CC_SYNTHESIZE(int, m_atkPower, AtkPower);

	/**	“GNPC‚ÌUŒ‚‚ğ¶¬
	*	@param enemy UŒ‚‚ğs‚È‚¤NPC
	*	@return	¶¬‚³‚ê‚½UŒ‚
	*/
	static EnemyAttack* create(Enemy *enemy);
	
	/**	“GNPC‚ÌUŒ‚
	*	@param enemy UŒ‚‚ğs‚È‚¤NPC
	*/
	void attack(Enemy *enemy);

	EnemyAttack();
	~EnemyAttack();

private:

	/**	UŒ‚‚Ì‰æ‘œƒtƒ@ƒCƒ‹‚ğw’è
	*	@param type “GNPC‚Ìí—Ş
	*	@return	í•Ê‚É‰‚¶‚½UŒ‚‚Ì‰æ‘œƒtƒ@ƒCƒ‹–¼
	*/
	std::string initFileName(enemyType type);

	/**	UŒ‚‚ÌˆÊ’u‚Æƒtƒ@ƒCƒ‹î•ñ‚ğİ’è
	*	@param enemy UŒ‚‚ğs‚È‚¤“GNPC
	*	@param point “GNPC‚ÌÀ•WiUŒ‚”­¶À•Wj
	*	@return	İ’è‚³‚ê‚½UŒ‚
	*/
	EnemyAttack* initEnemyAttack(Enemy *enemy, cocos2d::CCPoint point);

};

#endif /*defined(__WillYard__EnemyAttack__)*/
