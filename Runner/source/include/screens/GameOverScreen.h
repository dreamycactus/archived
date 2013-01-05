#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H


#include "../CGameState.h"
#include "../SDL_Helper.h"

#include "MainMenuScreen.h"
#include "GameScreen.h"

class GameOverScreen: public CGameState
{
    public:
        static GameOverScreen* instance() { return &inst; }
        bool Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleInput(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        ~GameOverScreen();

    protected:
         GameOverScreen();
    private:
        static GameOverScreen inst;
        bool quit, notPlayed;
        bool execute;
        int alpha;
        SDL_Surface *sprite1;
        SDL_Surface *sprite2;
        CSoundEffect soundSlash;

};

#endif // GAMEOVERSCREEN_H
