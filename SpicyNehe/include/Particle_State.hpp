#ifndef PARTICLE_STATE_H
#define PARTICLE_STATE_H

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

class Particle_State : public STATE::iGameState
{
    public:
        Particle_State();
        virtual ~Particle_State();

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

#endif // PARTICLE_STATE_H
