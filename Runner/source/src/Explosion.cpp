#include "../include/Explosion.h"


Explosion::Explosion(Vector2D p, double sr)
{
    pos = p;
    Done = false;
    anim.maxFrames = 4;
    anim.SetFrameRate(1);
    scrollRate = sr;

    sprite = load_image("sprites/explo.png");
    sound.load_sound("sounds/explo1.wav");
    sound.Play();

    SDL_Rect tempR;
    tempR.x = 0;
    tempR.w = 67;
    tempR.h = 67;
    for (unsigned int i = 0; i < 5; ++i)
    {
        tempR.y = i * 67;
        clips.push_back(tempR);
    }
}

void Explosion::Draw(CGameEngine* game, Vector2D p)
{
    Vector2D draw = Vector2D((pos.x) - p.x * scrollRate, pos.y);

    apply_surface(draw, sprite, game->GetScreen(), &clips[anim.GetCurrentFrame()]);
    if (anim.GetCurrentFrame() == anim.maxFrames - 1)
        Done = true;
    anim.OnAnimate();
}
