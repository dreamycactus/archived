#include <cassert>
#include "memory_macros.h"
#include "STATE_cGameStateManager.hpp"
#include "STATE_iGameState.hpp"
#include "STATE_cGameTransition.hpp"

#include "CORE_cGame.hpp"

using namespace STATE;

cGameStateManager::cGameStateManager(CORE::cGame* const game)
: m_Game(game)
, m_States()
{

}

cGameStateManager::~cGameStateManager()
{
    ClearAll();
}

void cGameStateManager::ReplaceStateUsingTransition(iGameState* new_state, cGameTransition* transition)
{
    assert(transition&&new_state);

    transition->SetOldAndNewState(m_States.back(), new_state);
    // Remove old state
    m_States.pop_back(); // Only pop. Transition still needs the old state, and it will delete old state upon finish
    // Push new state on stack
    m_States.push_back(new_state);
    m_States.back()->OnEnter(m_Game);
    m_States.back()->Pause(m_Game); // Pause new_state as we are transitioning
    // Push transition on stack
    m_States.push_back(transition);
    m_States.back()->OnEnter(m_Game);
}

void cGameStateManager::ReplaceState(iGameState* new_state)
{
    assert(new_state);

    if(!m_States.empty()) {
        m_States.back()->OnExit(m_Game);
        iGameState* stateToDelete = m_States.back();
        DELETESINGLE(stateToDelete);
        m_States.pop_back();
    }
    m_States.push_back(new_state);
    m_States.back()->OnEnter(m_Game);
}

void cGameStateManager::PushStateUsingTransition(iGameState* new_state, cGameTransition* transition)
{
    assert(transition&&new_state);

    iGameState* top = 0;

    if (!m_States.empty()) {
        top = m_States.back();
        m_States.back()->Pause(m_Game);
    }
    transition->SetOldAndNewState(top, new_state);
    // Push new state on stack
    m_States.push_back(new_state);
    m_States.back()->OnEnter(m_Game);
    m_States.back()->Pause(m_Game); // Pause new_state as we are transitioning
    // Push transition on stack
    m_States.push_back(transition);
    m_States.back()->OnEnter(m_Game);
}

void cGameStateManager::PushState(iGameState* new_state)
{
    assert(new_state);

    if (!m_States.empty()) {
        m_States.back()->Pause(m_Game);
    }
    // Push new state on stack
    m_States.push_back(new_state);
    m_States.back()->OnEnter(m_Game);
}

void cGameStateManager::PopStateUsingTransition(cGameTransition* transition)
{
    assert(transition&&m_States.size()>=2); // Need at least old and new state on stack to use transition effect

    transition->SetOldAndNewState(m_States.back(), m_States.back());
    m_States.pop_back();
    m_States.back()->Pause(m_Game);   // Pause new state
    // Push transition on stack
    m_States.push_back(transition);
    m_States.back()->OnEnter(m_Game);
}

void cGameStateManager::PopState()
{
    assert(!m_States.empty());
    // Leave old state
    m_States.back()->OnExit(m_Game);
    DELETESINGLE(m_States.back());
    m_States.pop_back();
    if (!m_States.empty()) {
        m_States.back()->Resume(m_Game);
    }
}

iGameState* cGameStateManager::GetCurrent() const
{
    /*DEBUG*/assert(m_States.back());
    return (m_States.empty()) ? 0 : m_States.back();
}

int cGameStateManager::GetNumStates() const
{
    return static_cast<int>(m_States.size());
}

void cGameStateManager::ClearAll()
{
    while (!m_States.empty()) {
        m_States.back()->OnExit(m_Game);
        DELETESINGLE(m_States.back());
        m_States.pop_back();
    }
}
