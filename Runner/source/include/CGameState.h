#ifndef CGAMESTATE_H
#define CGAMESTATE_H

#include "CGameEngine.h"


class CGameState
{
    public:
        virtual bool Init() = 0;
        virtual void Cleanup() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleInput(CGameEngine* game) = 0;
        virtual void Update(CGameEngine* game) = 0;
        virtual void Draw(CGameEngine* game) = 0;

        void ChangeState(CGameEngine* game, CGameState* state) { game->ChangeState(state); }

//    protected:
 //   private:
};

#endif // CGAMESTATE_H
