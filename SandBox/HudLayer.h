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
	
	/**	�_���[�W���x����ǉ�
	*	@param hudPos �Q�[���I�u�W�F�N�g�̈ʒu
	*	@param damage �\�����鐔�l
	*/
	void damageLabel(cocos2d::CCPoint hudPos, int damage);

	//�q�b�g�����x����\��
	void addHitCountLabel();

	//�q�b�g�����x�����\���ɂ��A�F��߂�
	void hideHitCountLabel();

	//HP���x����\�����A�X�V����
	void drawHpLabel();

	/**	HP���x�����\����
	*	@param flg �^�U
	*/
	void setHpLabelVisible(bool flg);

	/**	HP�o�[�w�i��HP�o�[��ǉ�
	*	@param obj �Q�[���I�u�W�F�N�g�i�v���C���[�ƓGNPC�j
	*/
	void initHpBar(GameObject *obj);

	/**	HP�o�[�Ƀ_���[�W�𔽉f
	*	@param obj �Q�[���I�u�W�F�N�g�i�v���C���[�ƓGNPC�j
	*/
	void drawHpBar(GameObject *obj);
	
	//Ready��ǉ�
	void readyImage();

	//Fire��ǉ�
	void fireImage();

	//Aim��ǉ�
	void aimImage();

	//touch!��ǉ�
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
