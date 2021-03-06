/*
* StateMachine.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "StateMachine.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {}

void StateMachine::pushState(GameState* pState)
{
	//コンテナの最後に新しい状態を追加
    m_gameStates.push_back(pState);
	//追加した状態（コンテナの最後）を取り出す。更に、その状態の初期化
    m_gameStates.back()->onStateEnter();
}

void StateMachine::changeState(GameState* pState) 
{
	//ステートが存在する場合
    if(!m_gameStates.empty())
    {
		//現在の状態と引数の状態が同一の場合、抜ける
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        
		//現在の状態と引数の状態が違う場合、状態終了の処理を実行し、現在の状態を削除
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
			//現在状態を削除（m_gameStates）
            m_gameStates.pop_back();
        }
        
		////コンテナの最後に新しい状態を追加
        m_gameStates.push_back(pState);
		//追加した状態（コンテナの最後）を取り出す。更に、その状態の初期化
        m_gameStates.back()->onStateEnter();
    }
}

void StateMachine::popState() 
{
	//ステートが存在する場合
    if(!m_gameStates.empty())
    {
		//状態終了の処理を実行し、現在の状態を削除
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
			//現在の状態を削除（m_gameStates）
            m_gameStates.pop_back();
        }
    }
}

void StateMachine::update(float dt) 
{
    m_gameStates.back()->stateUpdate(dt);
}

bool StateMachine::onBeganEvent()
{
	return m_gameStates.back()->onTouchBeganEvent();
}

void StateMachine::onMovedEvent()
{
	m_gameStates.back()->onTouchMovedEvent();
}

void StateMachine::onEndedEvent()
{
	m_gameStates.back()->onTouchEndedEvent();
}
