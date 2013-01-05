#include "../include/Doodad.h"

using std::string;

Doodad::Doodad(string temp, Vector2D p)
{
    sprite = load_image(temp);
    pos = p + Vector2D(0, -sprite->h);
    show = false;
}

void Doodad::SetPos(Vector2D p)
{
    show = true;
    pos = p + Vector2D(0, -sprite->h);;
}
void Doodad::Update(Vector2D p)
{
    if (pos.x + 100 + sprite->w  - p.x < 0)
        show = false;
}


void Doodad::Draw(CGameEngine *game, Vector2D p)
{
    if (show)
        apply_surface(pos - p, sprite, game->GetScreen());
}

void Doodad::Cleanup()
{
    SDL_FreeSurface(sprite);
}
