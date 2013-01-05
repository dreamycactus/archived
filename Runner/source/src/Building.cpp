#include "../include/Building.h"

Building::Building(Vector2D pos, int num, double slevel, int np, std::string spriteFiles)
{
    unsigned int i;
    SDL_Rect tempR;
    this->pos = pos + Vector2D(0, -slevel);
    numMiddles = num;
    numPieces = np;
    surfaceLevel = slevel;
    sprite = load_image(spriteFiles);


    tempR.y = 0;
    tempR.w = BLOCK_WIDTH;
    tempR.h = sprite->h;

    for (i = 0; i < numPieces; ++i)
    {
        tempR.x = i * BLOCK_WIDTH;
        clips.push_back(tempR);
    }
    for (i = 0; i < numMiddles; ++i)
        blocks.push_back(RandInt(1, numPieces-2));

    SDL_DisplayFormatAlpha(sprite);

    whole = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, BLOCK_WIDTH*(numMiddles+2), sprite->h, sprite->format->BitsPerPixel, sprite->format->Gmask, sprite->format->Gmask, sprite->format->Gmask, 255); //abosultely beautiful...

    apply_surface(Vector2D(0, 0), sprite, whole, &clips[0]);//left
    apply_surface(Vector2D((numMiddles+1) * BLOCK_WIDTH, 0), sprite, whole, &clips[numPieces-1]);//right
    for (unsigned int i = 0; i < numMiddles; ++i)
        apply_surface(Vector2D((i+1) * BLOCK_WIDTH, 0), sprite, whole, &clips[blocks[i]]);//middle
}

void Building::Draw(CGameEngine *game, Runner *player)
{
    apply_surface(pos - player->GetDrawX() + START_POS, whole, game->GetScreen());//

}

Vector2D Building::GetDrawPos()
{
    return pos;
}

Vector2D Building::GetColPos()
{
    return Vector2D(pos.x, pos.y + surfaceLevel);
}

Vector2D Building::GetBox()
{
    return Vector2D((numMiddles+2)*BLOCK_WIDTH, 1000);
}

void Building::Cleanup()
{
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(whole);
    blocks.clear();
    clips.clear();
}
