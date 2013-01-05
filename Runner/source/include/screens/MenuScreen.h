#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "../CGameState.h"
#include "../Runner.h"
#include "../SDL_Helper.h"


class MenuScreen: public CGameState
{
    public:
        static MenuScreen* instance();
        bool Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleInput(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        //~MenuScreen();

    protected:
        MenuScreen(){}

    private:
        static MenuScreen* inst;
        SDL_Surface *background;

};

#endif // MENUSCREEN_H
