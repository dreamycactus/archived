#include "../../include/doodads/Shot.h"

Shot::Shot(Vector2D pos, int duration, double top, double bot, std::vector<SDL_Rect> c, CAnimation a) : Thing(pos, Vector2D(0, 0))
{
    this->duration = duration;
    this->top = top;
    this->bot = bot;
    clip = c;
    anim = a;
    active = false;
    elapsed = 0;
}

void Shot::Init()
{
    active = false;
    elapsed = 0;
}

void Shot::Update(CGameEngine *game, Runner *player)
{
    if (active)
    {
        if (elapsed >= duration)
        {
            active = false;
            elapsed = 0;
        }
        ++elapsed;
        int ptop = player->GetPos().y;
        int pbot = ptop + player->GetBox().y;
        if ((ptop < bot && ptop > top) || (pbot > top && pbot < bot))
            player->Stumble();
        anim.OnAnimate(game);
    }
}

void Shot::Draw(CGameEngine *game, Runner *player)
{
    SDL_Rect c = clip[anim.GetCurrentFrame()];
    if (active)
        apply_surface(pos - player->GetPosX() + START_POS, sprite_sheet, game->GetScreen(), &c);
}

void Cleanup()
{

}

void AddClip(std::vector<SDL_Rect> c)
{

}
