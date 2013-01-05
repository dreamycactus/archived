/**
 *
 */

#include "STATE_cTransSquareSpin.hpp"

#include <GL/glu.h>
#include "CORE_cGame.hpp"
#include "MATH_Math.hpp"

using namespace STATE;
using namespace MATH;

namespace
{
        struct Quad
        {
            Vec2f v[4];
        };

        Quad square;
}

cTransSquareSpin::cTransSquareSpin()
: m_PercentDone(0.0f)
, m_AnimSpeed(0.001f)
{
    //ctor
}

cTransSquareSpin::~cTransSquareSpin()
{
    //dtor
}

bool cTransSquareSpin::OnEnter(CORE::cGame* game)
{
//    glViewport(0, 0, game->GetSDLState().window_w, game->GetSDLState().window_h);
//    glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
//    glLoadIdentity();											// Reset The Projection Matrix
//    // Set Up Ortho Mode To Fit 1/4 The Screen (Size Of A Viewport)
//    glOrtho(0, game->GetSDLState().window_w, game->GetSDLState().window_h, 0, -10.0, 10.0);
//
//    glMatrixMode(GL_MODELVIEW);								// Select The Projection Matrix
//    glLoadIdentity();

    m_PercentDone = 0.0f;
}

bool cTransSquareSpin::OnExit(CORE::cGame* game)
{
    // Must delete old state since GameStateManager does not know
    // when the transition is done with the old state
    m_pOldState->OnExit(game);
    DELETESINGLE(m_pOldState);
    return true;
}

void cTransSquareSpin::Update(CORE::cGame* game, float delta)
{
    square.v[0] = Vec2f(1.0f, 1.0f);
    square.v[1] = Vec2f(1.0f, 0.0f);
    square.v[2] = Vec2f(0.0f, 0.0f);
    square.v[3] = Vec2f(0.0f, 1.0f);




    for (int i=0; i<4; ++i) {
        square.v[i] *= 640.0f;
//        square.v[i].Rotate(m_PercentDone*180.0f);
    }

    m_PercentDone += delta * m_AnimSpeed;

    if (m_PercentDone >= 1.0f) {
        Finish(game);
    }
//    std::cout << m_PercentDone << std::endl;
}

void cTransSquareSpin::Render(CORE::cGame* game, float percent_tick)
{
    m_pOldState->Render(game, percent_tick);

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, 0);


    glBegin(GL_QUADS);
        glColor4f(0.0f, 0.0f, 0.0f, m_PercentDone);
        glVertex3f(square.v[0].x, square.v[0].y, 0.0f);
        glVertex3f(square.v[1].x, square.v[1].y, 0.0f);
        glVertex3f(square.v[2].x, square.v[2].y, 0.0f);
        glVertex3f(square.v[3].x, square.v[3].y, 0.0f);
    glEnd();

}
