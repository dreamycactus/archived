#include "../../include/backgrounds/Foreground.h"

Foreground::Foreground(int drawO, double sr)
{
    unsigned int i;
    sprites.push_back(load_image("sprites/backgrounds/tank1.png"));
    sprites.push_back(load_image("sprites/backgrounds/tank_leak.png"));
    sprites.push_back(load_image("sprites/backgrounds/eva.png"));
    srand((unsigned)time(NULL));
    CAnimation tempA;
    tempA.SetFrameRate(6);
    tempA.maxFrames = 1;
    anims.push_back(tempA);
    tempA.maxFrames = 3;
    anims.push_back(tempA);
    tempA.maxFrames = 11;
    anims.push_back(tempA);

    SDL_Rect tempR;
    vector<SDL_Rect> tempV;

    tempR.x = 0;
    tempR.y = 0;
    tempR.w = 210;
    tempR.h = 300;

    tempV.push_back(tempR);
    clips.push_back(tempV); // clip for tank
    tempV.clear();

    tempR.w = 380; //clip for tank leak...
    tempR.h = 300;
    for (i = 0; i < anims[BG_TANK_LEAK].maxFrames; ++i)
    {
        tempR.y = i * 300;
        tempV.push_back(tempR); //clip for tank leak...
    }
    clips.push_back(tempV);
    tempV.clear();

    tempR.w = 1024; //clip for eva...
    tempR.h = 480;
     for (i = 0; i < anims[BG_EVA].maxFrames; ++i)
    {
        tempR.y = i * 480;
        tempV.push_back(tempR); //clip for tank leak...
    }
    clips.push_back(tempV);
    tempV.clear();

    for (i = 0; i < 3; ++i)
        pos.push_back(Vector2D((double)i*RandDouble(5000, 30000), (double)(480-clips[i][0].h)));

    /* Set Collision Box for Items */
    tempR.x = -100;
    tempR.y = -500;
    tempR.w = sprites[0]->w+100;
    tempR.h = 1000;

    box.push_back(tempR); //tank

    tempR.w = sprites[1]->w+100;
    box.push_back(tempR); //tank leak'

    tempR.x = 200;
    tempR.w = 500;
    box.push_back(tempR);


    scrollRate = sr;
    drawOffset = drawO;

}

void Foreground::Update(CGameEngine *game, Vector2D p)
{
    unsigned int i;
    for (i = 0; i < 3; ++i)
    {
        if (CheckCol(Vector2D(p.x*scrollRate, 0), Vector2D(50, 50), Vector2D(0, 0), pos[i] + Vector2D(box[i].x, box[i].y), Vector2D(box[i].w, box[i].h)))
        {
            SDL_SetAlpha(sprites[i], SDL_SRCALPHA, 100);
        }
        else
            SDL_SetAlpha(sprites[i], SDL_SRCALPHA, 255);
    }
    Vector2D draw;
    for (i = 0; i < 3; ++i)
    {
        draw = pos[i] + Vector2D(-p.x*scrollRate + START_POS.x, 0);
        if (draw.x + (double)sprites[i]->w < 0)
        {
            pos[i].x += RandDouble(9000, 30000);
            anims[i].Reset();
        }
    }
}

void Foreground::Draw(CGameEngine *game, Vector2D p)
{
    Vector2D draw;
    for (unsigned int i = 0; i < 3; ++i)
    {
        draw = pos[i] + Vector2D(-p.x*scrollRate + START_POS.x, 0);
        if (draw.x + (double)sprites[i]->w > 0 && draw.x <= 1024)
        {
            apply_surface(draw, sprites[i], game->GetScreen(), &clips[i][anims[i].GetCurrentFrame()]);
            anims[i].OnAnimate();

        }
    }
    if (anims[2].GetCurrentFrame() == anims[2].maxFrames - 1)
        anims[2].Hold(true);


}
void Foreground::Cleanup()
{
    unsigned int i;
    for (i = 0; i < 3; ++i)
        SDL_FreeSurface(sprites[i]);
    sprites.clear();
}
