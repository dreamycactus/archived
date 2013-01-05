#include "../../include/obstacles/PlainObstacle.h"

using std::string;

PlainObstacle::PlainObstacle(Vector2D p, string fileName, int type)
{

    sprite = load_image(fileName);
    if (type == DOG_MAN)
        sound.load_sound("sounds/bark.wav");
    else
        sound.load_sound("sounds/chainsaw.wav");

    pos = p;
    colBox.x = sprite->w;
    colBox.y = sprite->w;

    detectionRange = 500;
    anim.maxFrames = 2;
    anim.SetFrameRate(2.5);

    for (unsigned int i = 0; i < 2; ++i)
    {
        clips[i].x = 0;
        clips[i].y = sprite->w * i;
        clips[i].w = sprite->w;
        clips[i].h = sprite->w;
    }
    Init();
}

void PlainObstacle::Init()
{
    shooterAlpha = 255;
    dieLoop = 0;
    state = SO_NEUTRAL;
}
void PlainObstacle::Update(CGameEngine *game, Runner *player)
{
    switch(state)
    {
        case SO_NEUTRAL:
            if (pos.x - player->GetPos().x < detectionRange)
            {
                state = SO_ALERT;
                sound.Play();
            }

            break;
        case SO_DEAD:
            shooterAlpha -= 30;
            pos.x += 6;
            if (shooterAlpha < 0)
            {
                if (dieLoop <= 2)
                {
                    shooterAlpha = 255;
                    ++dieLoop;
                }
                else
                    shooterAlpha = 0;


            }
            SDL_SetAlpha(sprite, SDL_SRCALPHA, shooterAlpha);
            return;
        default:
            break;
    }

    if (CheckCol(player->GetPos(), player->GetBox(), Vector2D(0, 0), pos + Vector2D(GetColBox()->x, GetColBox()->y), Vector2D(GetColBox()->w, GetColBox()->h)))
        player->Stumble();
}
void PlainObstacle::Draw(CGameEngine *game, Runner *player)
{
    SDL_Rect clip;
    if (state != SO_NEUTRAL)
    {
        clip = clips[anim.GetCurrentFrame()];
        anim.OnAnimate();
    }
    else
        clip = clips[0];

    apply_surface(pos - player->GetDrawX() + START_POS, sprite, game->GetScreen(), &clip);
}

void PlainObstacle::Kill(int k)
{
    state = SO_DEAD;
}

SDL_Rect* PlainObstacle::GetColBox()
{
    SDL_Rect tempR;
    tempR.x = 5;
    tempR.y = 1;
    tempR.w = colBox.x;
    tempR.h = colBox.y;
    return &tempR;
}
