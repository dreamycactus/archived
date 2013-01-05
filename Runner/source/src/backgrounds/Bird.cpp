#include "../../include/backgrounds/Bird.h"

Bird::Bird(string fileName, double dr, double rateSin, double rateX, double frameRate)
{
    SDL_Rect tempR;
    const int BIRD_SPRITES = 4;

    sprites = load_image(fileName);
    soundFlap.load_sound("sounds/flap.wav");
    this->detectionRange = dr;
    this->rateSin = rateSin;
    this->rateX = rateX;
    anim.SetFrameRate(0);
    anim.maxFrames = BIRD_SPRITES;

    tempR.h = tempR.w = BIRD_LEN;
    tempR.y = facing * BIRD_LEN;
    for (unsigned int i = 0; i < anim.maxFrames; ++i)
    {
        tempR.x = i * BIRD_LEN;
        clips.push_back(tempR);
    }
}
void Bird::Init(Vector2D pos, int facing, double speed)
{
    this->pos = pos;
    this->origin = pos;
    this->facing = facing;
    this->speed = speed;

    state = STANDING;
    t = 0;

    for (unsigned int i = 0; i < clips.size(); ++i)
    {
        clips[i].y = facing * BIRD_LEN;
    }
}
/* Remember y = k*x + c*sin(x) */

void Bird::Update(Vector2D p, double sr)
{
    if (state == STANDING && pos.x - p.x*sr  < detectionRange)
    {
        state = FLYING;
        soundFlap.Play();
    }


    if (state == FLYING)
    {
        t += speed;
        if (facing == LEFT)
            pos.x = -t + origin.x;
        else
            pos.x = t + origin.x;
        pos.y =  rateX*(-t) + rateSin * sin(-t/3.5) + origin.y;
        anim.OnAnimate();
    }
    if (pos.y + BIRD_LEN < 0)
        state = HIDDEN;

}
void Bird::Draw(CGameEngine *game, Vector2D p, double sr)
{
    if (state == HIDDEN)
        return;
    Vector2D draw = Vector2D((pos.x) - p.x * sr, pos.y + (double) BIRD_OFFSET_Y);
    apply_surface(draw, sprites, game->GetScreen(), &clips[anim.GetCurrentFrame()]);
}

void Bird::Cleanup()
{
    SDL_FreeSurface(sprites);
    sprites = NULL;
    soundFlap.Cleanup();
}
