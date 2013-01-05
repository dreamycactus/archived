#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "../SDL_helper.h"
#include "../CGameState.h"

#define MAIN     0
#define CREDIT   1
#define INSTR    2

class MainMenuScreen: public CGameState
{
    public:
        static MainMenuScreen* instance() { return &inst; }
        bool Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleInput(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);


    protected:
        MainMenuScreen(){}

    private:
        static MainMenuScreen inst;
        SDL_Surface *sprite_bg;
        SDL_Surface *sprite_bg_instr;
        SDL_Surface *sprite_bg_credit;
        SDL_Surface *sprite_play;
        SDL_Surface *sprite_quit;
        SDL_Surface *sprite_instr;
        SDL_Surface *sprite_credit;
        Mix_Music *music1;

        int state;
        bool guard;

};

#endif // MAINMENUSCREEN_H
