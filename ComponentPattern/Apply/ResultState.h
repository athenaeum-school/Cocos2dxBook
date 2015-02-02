/*
* ResultState.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ResultState__
#define __WillYard__ResultState__

#include "GameState.h"
#include <cocos2d.h>
#include "AudioComponent.h"

class ResultState : public GameState
{
public:

	bool onStateEnter() override;
	bool onStateExit() override;
	void stateUpdate(float dt) override;
	bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;

	std::string getStateID() override { return s_resultID; }
	
	ResultState();
	~ResultState();

private:

	AudioComponent *m_pAudio;
	int m_timer;
	static const std::string s_resultID;

	void resultToNormal();
	void resultToTitle();

	//���g���C�A�o�b�N�{�^����\��
	void onResult();

	/**	�{�^���������A�v���C���[�^�[���֑J�ڂ���R�[���o�b�N�֐�
	*	@param pSender menuSelector�̈����̈����̌^
	*/
	void retry(cocos2d::CCObject* pSender);

	/**	�{�^���������A�^�C�g����ʂ֑J�ڂ���R�[���o�b�N�֐�
	*	@param pSender menuSelector�̈����̈����̌^
	*/
	void back(cocos2d::CCObject* pSender);
	
};

#endif /* defined(__WillYard__ResultState__) */
