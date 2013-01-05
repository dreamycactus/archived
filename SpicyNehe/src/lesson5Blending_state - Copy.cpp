#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include "demo_cLesson5Blending.hpp"
#include "CORE_cGame.hpp"
#include "GFX_cImage.hpp"
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_GfxHelper.hpp"

    #include <iostream>
    using namespace std;

using namespace GFX;
using namespace GFX::G2D;

cLesson5Blending::cLesson5Blending() {}
cLesson5Blending::~cLesson5Blending() {}

STATE::iGameState* cLesson5Blending::CreateInstance()
{
    return new cLesson5Blending;
}
STATE::iGameState* cLesson5Blending::Clone()
{
    return new cLesson5Blending;
}

cTexture* p_tex;
//cTexture* p_tex2;
bool cLesson5Blending::OnEnter()
{
    cout << "Entering State\n";
    p_tex = new cTexture("art/tilez.png");
    p_tex->RegisterGL();
    test = false;

    return true;
}
bool cLesson5Blending::OnExit()
{
    cout << "Leaving state\n";
}
void cLesson5Blending::Pause() {}
void cLesson5Blending::Resume() {}




void cLesson5Blending::Update(CORE::cGame* game, float delta)
{
    HandleInput(game);
}

void cLesson5Blending::Render(CORE::cGame* game, float percent_tick)
{
    static G2D::cSpriteBatch batch = G2D::cSpriteBatch();

    static cTextureRegion reg = cTextureRegion(*p_tex);
//    static cTextureRegion reg2 = cTextureRegion(*p_tex2);


    glEnable(GL_ALPHA_TEST) ;
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);


    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
//    ImmediateRenderTexturePos2Dim2(*p_tex, 0.0, 0.0f, 1.0f, 1.0f);

    batch.Begin();
//        batch.DrawTexture(*p_tex2, 0.0f, 3.0f, 1.0f, 1.0f);
        if (test) batch.DrawTexture(reg, 0.0f, 0.0f, 4.0f, 1.0f);
//        batch.DrawTexturePos2Dim2Origin2Scale2Rot(reg, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 45.0f);

    batch.End();
}

void cLesson5Blending::HandleInput(CORE::cGame* game)
{
    CORE::Input& input = game->GetInput();

    if (input.GetKeyState(HAR_ESCAPE)) game->EndGame();
    if (input.OnKeyDown(HAR_a)) { test = !test; }
    if (input.OnKeyDown(HAR_b)) { game->GetStateManager().ReplaceState(game->state_factory.CreateObject("game")); }

}
