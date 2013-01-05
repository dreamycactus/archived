#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H

#include <vector>
#include "SDL_Helper.h"
#include "Timer.h"




class CGameState;

class CGameEngine
{
    public:
        CGameEngine();

        bool Init(int screen_w, int screen_h, int screen_bpp);
        void Cleanup();

        void ChangeState(CGameState* state);
        void PushState(CGameState* state);
        void PopState();

        void HandleInput();
        void Update();
        void Draw();

        bool Running() { return m_running; }
        void Quit();

        Uint32 GetTicks();
        long GetFrames() { return frames; }
        void IncFrames() { ++frames; }


        SDL_Surface* GetScreen();
        SDL_Event GetEvent();
        int GetWidth();

        void SetEvent(SDL_Event event);



    private:

        std::vector<CGameState*> states;
        SDL_Event event;
        SDL_Surface *screen;
        long frames;

        Timer game_timer;

        bool m_running;
        int screen_w;
        int screen_h;
        int screen_bpp;
};

#endif // CGAMEENGINE_H
