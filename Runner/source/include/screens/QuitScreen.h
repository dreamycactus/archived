#ifndef QUITSCREEN_H
#define QUITSCREEN_H

#include "../CGameState.h"

class QuitScreen: public CGameState
{
    public:
        static QuitScreen* instance() { return &inst; }
        bool Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleInput(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        ~QuitScreen();

    protected:
         QuitScreen();
    private:
        static QuitScreen inst;

};

#endif // QUITSCREEN_H
