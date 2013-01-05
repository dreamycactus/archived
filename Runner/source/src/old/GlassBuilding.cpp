#include "../include/GlassBuilding.h"

GlassBuilding::GlassBuilding(Vector2D pos, Vector2D box, Vector2D posTop, Vector2D boxTop, bool glass)
{
    this->pos = pos;
    this->box = box;
    this->boxTop = boxTop;
    this->posTop = posTop;
    this->glass = glass;

}

void GlassBuilding::Init()
{
        sprite_top = load_image("sprites/top_build.png");
        sprite_inside = load_image("sprites/inside_build.png");
        sprite_bot = load_image("sprites/bot_build.png");
        paneState[0] = ALIVE;
        paneState[1] = ALIVE;
        if(glass)
        {
            glasses[0] = new Glass(Vector2D(pos.x, posTop.y+boxTop.y), GLASS_BOX);
            glasses[1] = new Glass(Vector2D(pos.x+box.x, posTop.y+boxTop.y), GLASS_BOX);
            glasses[0]->Init();
            glasses[1]->Init();

        }
}

void GlassBuilding::Cleanup()
{
    glasses[0]->Cleanup();
    glasses[1]->Cleanup();
    delete glasses[0];
    delete glasses[1];
    SDL_FreeSurface(sprite_top);
    SDL_FreeSurface(sprite_inside);
    SDL_FreeSurface(sprite_bot);
}

void GlassBuilding::Update(CGameEngine *game, Runner *player)
{
    glasses[0]->Update(game, player);
    glasses[1]->Update(game, player);
}

void GlassBuilding::Draw(CGameEngine *game, Runner *player)
{

    apply_surface(posTop - player->GetDrawX() + START_POS, sprite_top, game->GetScreen());
    apply_surface(posTop+ Vector2D(0, boxTop.y) - player->GetDrawX() + START_POS, sprite_inside, game->GetScreen());
    apply_surface(pos - player->GetDrawX() + START_POS, sprite_bot, game->GetScreen());
    glasses[0]->Draw(game, player);
    glasses[1]->Draw(game, player);
}

Vector2D GlassBuilding::GetPosTop()
{
    return posTop;
}
Vector2D GlassBuilding::GetBoxTop()
{
    return boxTop;
}
