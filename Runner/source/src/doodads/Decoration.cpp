#include "../../include/doodads/Decoration.h"

Decoration::Decoration(Vector2D pos, SDL_Surface *sprite) : Thing(pos, Vector2D(0,0))
{
    this->sprite = sprite;
}

void Decoration::Draw(CGameEngine *game, Runner *player)
{

}
