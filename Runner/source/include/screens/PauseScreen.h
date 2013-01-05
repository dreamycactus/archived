#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "../SDL_helper.h"
#include "../CGameState.h"
#include "../PauseMenu.h"


class PauseScreen: public CGameState
{
    public:
        static PauseScreen* instance() { return &inst; }
        bool Init();
        void Cleanup();

        void Pause() {}
        void Resume() {}

        void HandleInput(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);


    protected:
        PauseScreen(){}

    private:
        static PauseScreen inst;

};

#endif // PAUSESCREEN_H
