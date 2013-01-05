////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CTimer.h
 * \author  Hua Fei Yu 0951402
 * \date    September 22, 2011
 * \brief   Timer utility classed adapted from Lazy Foo's tutorial
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef CTIMER_H
#define CTIMER_H

// Headers
#include "SDL/SDL.h"

class CTimer
{
    public:
        //Initializes variables
                                CTimer();
        virtual                 ~CTimer();

        //The various clock actions
        void                    start();
        void                    stop();
        void                    pause();
        void                    unpause();

        //Gets the timer's time
        Uint32                  get_ticks();
        Uint32                  get_delta();

        //Checks the status of the timer
        bool                    isStarted() { return started_; }
        bool                    isPaused()  { return paused_; }

    private:
        //The clock time when the timer started
        Uint32                  start_ticks_;
        Uint32                  old_ticks_;

        //The ticks stored when the timer was paused
        int                     paused_ticks_;

        //The timer status
        bool                    paused_;
        bool                    started_;


};

#endif // CTIMER_H
