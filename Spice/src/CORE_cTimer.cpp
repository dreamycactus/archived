#include "SDL2/SDL.h"
#include "CORE_cTimer.hpp"


using namespace CORE;

cTimer::cTimer() :
    m_ticks_since_start(0),
    m_ticks_since_pause(0),
    m_is_paused(false),
    m_is_started(false) {}

cTimer::~cTimer() {}

//The various clock actions
void cTimer::Start()
{
    m_is_started = true;
    m_is_paused = false;
    m_ticks_since_start = SDL_GetTicks();
}
void cTimer::Stop()      { m_is_paused = m_is_started = false; }

void cTimer::Pause()
{
    if ((m_is_started == true) && (m_is_paused == false))
    {
        m_is_paused = true;
        m_ticks_since_pause = SDL_GetTicks() - m_ticks_since_start;
    }
}
void cTimer::Unpause()
{
    if(m_is_paused == true)
    {
        m_is_paused = false;
        m_ticks_since_start = SDL_GetTicks() - m_ticks_since_pause;
        m_ticks_since_pause = 0;
    }
}

//Gets the timer's time
Uint32 cTimer::GetTicksSinceStart() const
{
    if(m_is_started == true)
    {
        if(m_is_paused == true) { return m_ticks_since_pause; }
        else { return SDL_GetTicks() - m_ticks_since_start; }
    }
    return 0;
}

Uint32 cTimer::GetTicksDelta()
 {
    if(m_is_started == true)
    {
        if(m_is_paused == true) { return m_ticks_since_pause; }
        else
        {
            Uint32 delta;

            m_ticks_since_start = SDL_GetTicks();
            delta = m_ticks_since_start - m_old_ticks;
            m_old_ticks = m_ticks_since_start;
            return delta;
        }
    }
    return 0;
}

//Checks the status of the timer
bool cTimer::IsStarted() { return m_is_started; }
bool cTimer::IsPaused()  { return m_is_paused; }
