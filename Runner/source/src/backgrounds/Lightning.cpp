#include "../../include/backgrounds/Lightning.h"

using std::vector;
using std::string;

Lightning::Lightning()
{
    SDL_Rect tempR;
    flashAlpha = 255;
    showLight = showFlash = false;
    nextStrike = 0;
    thunderTime = 0;
    pos.x = 400; pos.y = 0;
    sprites.push_back(load_image("sprites/backgrounds/light1.png"));
    sprites.push_back(load_image("sprites/backgrounds/light2.png"));
    sprites.push_back(load_image("sprites/backgrounds/light3.png"));

    tempR.y = 0; tempR.w = 200; tempR.h = 480;
    for (unsigned int i = 0; i < 5; ++i)
    {
        tempR.x = i * 200;
        clips.push_back(tempR);
    }
    anim.maxFrames = 5;
    anim.SetFrameRate(4.0);
    sound.load_sound("sounds/thunder.wav");
    thundered = true;
}

void Lightning::Update(Vector2D p)
{
    if (thunderTime < p.x && !sound.IsPlaying())
    {
        sound.Play();
        thundered = true;
    }

    if (p.x > nextStrike && !showLight && thundered)
    {
        anim.Reset();
        showLight = true;
        thundered = false;
        nextStrike = RandDouble(20000, 50000) + p.x;
        thunderTime = RandDouble(-1, 7000) + nextStrike;
        pos.x = RandDouble(0, 824);
        indexSprite = RandInt(0, sprites.size()-1);
        oscillateMax = RandInt(0, 1); //total number of flashes for this lightning strike
        oscillateCount = 0; //remember number of flashes on screen
        flashDelta = 40;
    }



}
void Lightning::Draw(CGameEngine *game, Vector2D p)
{
    if (showLight)
        apply_surface(pos, sprites[indexSprite], game->GetScreen(), &clips[anim.GetCurrentFrame()]);

    if (anim.GetCurrentFrame() == 1)
        showFlash = true;
    if (anim.GetCurrentFrame() == anim.maxFrames - 1)
        showLight = false;
    if (showLight)
        anim.OnAnimate();
}

void Lightning::Flash(CGameEngine *game)
{
    if (showFlash)
    {
        SDL_Surface *temp = SDL_CreateRGBSurface(SDL_HWSURFACE, game->GetScreen()->w,game->GetScreen()->h, 32, 0 , 0,  0, 0);
        SDL_FillRect(temp, &temp->clip_rect, SDL_MapRGB(game->GetScreen()->format, 255, 255, 255));
        SDL_SetAlpha (temp, SDL_SRCALPHA, flashAlpha) ;
        apply_surface(Vector2D(0, 0), temp, game->GetScreen());
        SDL_FreeSurface(temp);

        flashAlpha -= flashDelta;
        if (flashAlpha < 0)
        {
            if (oscillateCount == oscillateMax)
                flashDelta = 3;
            else if (oscillateCount > oscillateMax)
                showFlash = false;

            flashAlpha = 255;
            ++oscillateCount;


        }
    }

}

void Lightning::Cleanup()
{
    for(unsigned int i = 0; i < sprites.size(); ++i)
    {
        SDL_FreeSurface(sprites[i]);
    }
    sprites.clear();
    sound.Cleanup();
}
