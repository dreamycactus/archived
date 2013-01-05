#include "../include/Particle.h"

Particle::Particle()
{

}

Particle::Particle(Vector2D pos, Vector2D box, Vector2D velocity, Vector2D acceleration)
{
    this->pos = pos;
    this->box = box;
    this->velocity = velocity;
    this->acceleration = acceleration;
    {
    clip1[ 0 ].x = 16;
    clip1[ 0 ].y = 0;
    clip1[ 0 ].w = 8;
    clip1[ 0 ].h = 8;

    clip1[ 1 ].x = 24;
    clip1[ 1 ].y = 0;
    clip1[ 1 ].w = 8;
    clip1[ 1 ].h = 8;

    clip1[ 2 ].x = 8 * 4;
    clip1[ 2 ].y = 0;
    clip1[ 2 ].w = 8;
    clip1[ 2 ].h = 8;

    clip1[ 3 ].x = 8 * 5;
    clip1[ 3 ].y = 0;
    clip1[ 3 ].w = 8;
    clip1[ 3 ].h = 8;
    }
    pos = Vector2D(0.0, 0.0);
    velocity = Vector2D(0.0, 0.0);
    sprite_sheet = load_image( "sprites/glass.png" );
    frame = 0;
    state = ALIVE;

}


void Particle::Update(CGameEngine *game, Runner *player)
{
    if (state == GONE)
        return;
    else
        ++lifeElapsed;

    velocity += acceleration;
    pos += velocity;
    frame++;
    if (frame >= 4)
        frame = 0;


}
void Particle::Draw(CGameEngine *game, Runner *player)
{
    SDL_Rect clip = clip1[frame];
    apply_surface(pos - player->GetDrawX() + START_POS, sprite_sheet, game->GetScreen(), &clip);
}

void Particle::SetVelocity(Vector2D velocity)
{
    this->velocity = velocity;
}
void Particle::Cleanup()
{
    SDL_FreeSurface(sprite_sheet);
}
