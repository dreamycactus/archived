#include "../../include/backgrounds/Tram.h"

Tram::Tram(Vector2D p, double sr)
{
    pos = p;
    oMax = pos.y; oMin = pos.y - 1;
    scrollRate = sr;
    state = TRAM_NORMAL;
    sprite = load_image("sprites/backgrounds/tram.png");
    sprite_explo = load_image("sprites/backgrounds/explo.png");
    shakeVel = -1;
    alpha = 255;
    dieLoop = 0;
    maxExplosions = 17;
    numExplosions = 0;
}

void Tram::Update(CGameEngine *game, Vector2D p)
{
    if (state == TRAM_SHAKE)
    {
        alpha -= 30;
        if (alpha < 0)
        {
            if (dieLoop <= 10)
            {
                alpha = 255;
                ++dieLoop;
            }
            else
                alpha = 0;


        }
        SDL_SetAlpha(sprite, SDL_SRCALPHA, alpha);

        if (RandInt(0, 5) == 2 && numExplosions < maxExplosions)
        {
            explosions.push_back(new Explosion(pos + Vector2D(RandDouble((double)-70, (double)TRAM_WIDTH), RandDouble(-20, 20)), scrollRate));
            ++numExplosions;
        }

        pos.y += shakeVel;
        if (pos.y >= oMax || pos.y <= oMin)
            shakeVel *= -1;
    }
    for (unsigned int i = 0; i < explosions.size(); ++i)
    {
        if (explosions[i]->Done)
        {
            explosions[i]->Cleanup();
            delete explosions[i];
            explosions.erase(explosions.begin() + i);
            break;
        }
    }
}

void Tram::Draw(CGameEngine *game, Vector2D p)
{
    Vector2D draw = Vector2D((pos.x) - p.x * scrollRate, pos.y);
    if (state != TRAM_DEAD)
        apply_surface(draw, sprite, game->GetScreen());
    for (unsigned int i = 0; i < explosions.size(); ++i)
        explosions[i]->Draw(game, p);
}

void Tram::Cleanup()
{
    SDL_FreeSurface(sprite);
}

void Tram::Move(Vector2D p)
{
    pos += p;
}
