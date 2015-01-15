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

	CC_SYNTHESIZE(int, _comboCount, ComboCount);
	CC_SYNTHESIZE(AnimationManager *, _anime, Anime);

	virtual bool init();
	void update(float dt);
	CREATE_FUNC(HudLayer);
	
	float CalcDiff(float nextPos, float getPos);
	float Calc(float powOne, float powTwo);
	bool isLessThanDist(float dist, float radius);
	void toString(int value);
	void damageToString(cocos2d::CCPoint hudPos, int damage);
	void addComboCount();
	void hide();
	void drawMyHpLabel();
	void setLabelVisible(bool flg);

	HudLayer();
	~HudLayer();

private:

	cocos2d::CCLabelTTF *_label;
	cocos2d::CCLabelTTF *_comboLabel;
	cocos2d::CCLabelTTF *_hp_label_wisp;
	MainScene *_main;
	static HudLayer *s_pInstance;
	
};

typedef HudLayer Hud;

#endif /*defined(__WillYard__HudLayer__)*/
