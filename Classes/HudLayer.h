/*
* HudLayer.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__HudLayer__
#define __WillYard__HudLayer__

#include "cocos2d.h"
#include "GameObject.h"
#include "ActionManager.h"

class MainScene;

class HudLayer : public cocos2d::CCLayer
{
public:

	static HudLayer* getInstance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new HudLayer();
			return s_pInstance;
		}

		return s_pInstance;
	}

	CC_SYNTHESIZE(int, m_hitCount, HitCount);
	CC_SYNTHESIZE_RETAIN(ActionManager *, m_pAction, Action);

	CREATE_FUNC(HudLayer);
	virtual bool init();
	
	/**	ダメージラベルを追加
	*	@param hudPos ゲームオブジェクトの位置
	*	@param damage 表示する数値
	*/
	void damageLabel(cocos2d::CCPoint hudPos, int damage);

	//ヒット数ラベルを表示
	void addHitCountLabel();

	//ヒット数ラベルを非表示にし、色を戻す
	void hideHitCountLabel();

	//HPラベルを表示し、更新する
	void drawHpLabel();

	/**	HPラベルを非表示に
	*	@param flg 真偽
	*/
	void setHpLabelVisible(bool flg);

	/**	HPバー背景とHPバーを追加
	*	@param obj ゲームオブジェクト（プレイヤーと敵NPC）
	*/
	void initHpBar(GameObject *obj);

	/**	HPバーにダメージを反映
	*	@param obj ゲームオブジェクト（プレイヤーと敵NPC）
	*/
	void drawHpBar(GameObject *obj);
	
	//Readyを追加
	void readyImage();

	//Fireを追加
	void fireImage();

	//Aimを追加
	void aimImage();

	//touch!を追加
	void touchImage();
	
private:

	static HudLayer *s_pInstance;
	
	cocos2d::CCLabelTTF *m_pLabel;
	cocos2d::CCLabelTTF *m_pHitCountLabel;
	cocos2d::CCLabelTTF *m_pPlayerHpLabel;
	
	HudLayer();
	~HudLayer();

};

typedef HudLayer Hud;

#endif /* defined(__WillYard__HudLayer__) */
