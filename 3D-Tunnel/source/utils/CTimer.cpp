#include "CTimer.h"


CTimer::CTimer()
{
    //Initialize the variables
    start_ticks_    = 0;
    paused_ticks_   = 0;
    paused_         = false;
    started_        = false;
}

CTimer::~CTimer()
{

}

void CTimer::start()
{
    started_ = true;
    paused_ = false;
    start_ticks_ = SDL_GetTicks();
}
void CTimer::stop()
{
    started_ = false;
    paused_  = false;
}
void CTimer::pause()
{
    if ((started_ == true) && (paused_ == false))
    {
        paused_ = true;
        paused_ticks_ = SDL_GetTicks() - start_ticks_;
    }
}
void CTimer::unpause()
{
    if(paused_ == true)
    {
        paused_ = false;
        start_ticks_ = SDL_GetTicks() - paused_ticks_;
        paused_ticks_ = 0;
    }
}

Uint32 CTimer::get_ticks()
{
    if(started_ == true)
    {
        if(paused_ == true)
        {
            return paused_ticks_;
        }
        else
        {
            return SDL_GetTicks() - start_ticks_;
        }
    }
    return 0;
}

Uint32 CTimer::get_delta()
{
    if(started_ == true)
    {
        if(paused_ == true)
        {
            return paused_ticks_;
        }
        else
        {
            Uint32 delta;

            start_ticks_ = SDL_GetTicks();
            delta = start_ticks_ - old_ticks_;
            old_ticks_ = start_ticks_;
            return delta;
        }
    }
    return 0;
}
