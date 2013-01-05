#ifndef CTIMER_H
#define CTIMER_H

#include <SDL2/SDL.h>
// Headers


namespace CORE
{

    class cTimer
    {
    public:
        // Initialises variables
                                cTimer();

        virtual                 ~cTimer();

        // The various clock actions
        void                    Start();
        void                    Stop();
        void                    Pause();
        void                    Unpause();

        // Gets the timer's time
        Uint32                  GetTicksSinceStart() const;
        // Get ticks since last call to this function
        Uint32                  GetTicksDelta();

        // Checks the status of the timer
        bool                    IsStarted();
        bool                    IsPaused();

    private:
        //The clock time when the timer started
        Uint32                  m_ticks_since_start;
        Uint32                  m_old_ticks;

        //The ticks stored when the timer was paused
        Uint32                  m_ticks_since_pause;

        //The timer status
        bool                    m_is_paused;
        bool                    m_is_started;


    };

}

#endif // CTIMER_H
