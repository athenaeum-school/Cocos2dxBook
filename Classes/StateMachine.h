/*
* StateMachine.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__StateMachine__
#define __WillYard__StateMachine__

#include <vector>
#include "GameState.h"

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();
    
	std::vector<GameState*> getStates(){ return m_gameStates; }
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update(float dt);
    bool onBeganEvent();
	void onMovedEvent();
	void onEndedEvent();
    
protected:
private:
    std::vector<GameState*> m_gameStates;
};

typedef StateMachine theStateMachine;

#endif /* defined(__WillYard__StateMachine__) */
