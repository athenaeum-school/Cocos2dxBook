/*
* TitleState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__TitleState__
#define __WillYard__TitleState__

#include "GameState.h"
#include <cocos2d.h>
#include "AudioComponent.h"

class TitleState : public GameState
{
public:

	CC_SYNTHESIZE(bool, m_isPlayBGM, IsPlayBGM);

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

	std::string getStateID() override { return s_titleID; }
	
	TitleState();
	~TitleState();

private:

	int m_timer;
	static const std::string s_titleID;
	AudioComponent *m_pAudio;
	
	void titleToNormal();

	//�X�^�[�g�{�^����\��
	void onNormal();

	/**	�w�i��ǉ�
	*	@param screenSize ��ʃT�C�Y
	*/
	void initBackground(cocos2d::CCSize screenSize);

	/**	�{�^���������A�v���C���[�^�[���֑J�ڂ���R�[���o�b�N�֐�
	*	@param pSender menuSelector�̈����̈����̌^
	*/
	void play(cocos2d::CCObject *pSender);

};

#endif /* defined(__WillYard__TitleState__) */
