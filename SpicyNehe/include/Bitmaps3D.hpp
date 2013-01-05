#ifndef BITMAPS3D_STATE_H
#define BITMAPS3D_STATE_H

#include "STATE_iGameState.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
//
/*temp*/#include <iostream>

namespace CORE
{
    class cGame;
    class Input;
}

//static STATE::iGameState* CreateInstance() {}

class Bitmaps3DState: public STATE::iGameState
{
    public:
        Bitmaps3DState();
        virtual ~Bitmaps3DState();

        static STATE::iGameState* CreateInstance();
        virtual STATE::iGameState* Clone(); // Ideally this function should return a copy, not a blank instance

        bool OnEnter();
        bool OnExit();
        void Pause();
        void Resume();

        void HandleInput(CORE::cGame* game);
        void Update(CORE::cGame* game, float delta);

        void Render(CORE::cGame* game, float percent_tick);

    private:
        GFX::G2D::cSpriteBatch m_batch;
        bool test;
};

#endif // BITMAPS3D_STATE_H
