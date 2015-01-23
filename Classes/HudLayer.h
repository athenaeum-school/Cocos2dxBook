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
#include "AnimationManager.h"

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

	CC_SYNTHESIZE(int, m_comboCount, ComboCount);
	CC_SYNTHESIZE_RETAIN(AnimationManager *, m_pAnime, Anime);

	virtual bool init();
	CREATE_FUNC(HudLayer);
	
	void damageToString(cocos2d::CCPoint hudPos, int damage);
	void addComboCount();
	void hide();
	void drawHpLabel();
	void setLabelVisible(bool flg);
	void ready();
	void fire();
	void aim();
	void touchImage();
	void initHpbar(GameObject *obj);
	void drawHpbar(GameObject *obj);

private:

	static HudLayer *s_pInstance;
	
	cocos2d::CCLabelTTF *m_pLabel;
	cocos2d::CCLabelTTF *m_pComboLabel;
	cocos2d::CCLabelTTF *m_pPlayerHpLabel;
	
	HudLayer();
	~HudLayer();

};

typedef HudLayer Hud;

#endif /*defined(__WillYard__HudLayer__)*/
