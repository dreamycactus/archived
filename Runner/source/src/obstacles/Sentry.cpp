#include "../../include/obstacles/Sentry.h"

Sentry::Sentry(Vector2D pos)
{
    unsigned int i;

    this->pos = pos;

    detectionRange = 700;
    attackRange = 500;
    shotOffset = 9;

    weapDuration = 5;
    weapLevelMin = 30;
    weapLevelMax = 75;

    anim_beam.SetFrameRate(.9);
    anim_beam.maxFrames = 15;

    sprite = load_image("sprites/obstacles/sentry.png");
    sprite_beam = load_image("sprites/obstacles/sentry_blast.png");

    colBox.w = sprite->w;
    colBox.h = sprite->h;


    for (i = 0; i < anim_beam.maxFrames; ++i)
    {
        clip_beam[i].x = 0;
        clip_beam[i].y = i * 55;
        clip_beam[i].w = sprite_beam->w;
        clip_beam[i].h = 55;

    }
    Init();
}

void Sentry::Init()
{
    sound.load_sound("sounds/tractorbeam.wav");
    state = SO_NEUTRAL;
    dieLoop = 0;
    weapActive = false;
    weapElapsed = 0;
    shooterAlpha = 255;
    hp = 2;
    shot = false;
}

void Sentry::Update(CGameEngine *game, Runner *player)
{
    double attackRangeMin = 50;
    switch(state)
    {
        case SO_NEUTRAL:
            if (pos.x - player->GetPos().x < detectionRange)
            {
                if (!shot)
                {
                    state = SO_ALERT;
                }

            }
            break;
        case SO_ALERT:
            if (pos.x - player->GetPos().x < attackRange)
            {
                state = SO_SHOOT;
                shot = true;
                sound.Play(-1);
            }
            break;
        case SO_SHOOT:
            if (anim_beam.GetCurrentFrame() == shotOffset) //if the beam is out
                weapActive = true;
            if (weapActive && weapElapsed < weapDuration)
            {
                int ptop = player->GetPos().y;
                int pbot = ptop + player->GetBox().y;
                int wtop = pos.y + weapLevelMin;
                int wbot = pos.y + weapLevelMax;

                if (!(pbot < wtop || ptop > wbot)) //if the bullet is on same level as player
                    player->Stumble();

                ++weapElapsed;
            }
            else
                weapActive = false;

            break;
        case SO_DEAD:
            shooterAlpha -= 40;
            pos.x += 1;
            if (shooterAlpha < 0)
            {
                if (dieLoop <= 2)
                {
                    shooterAlpha = 230;
                    ++dieLoop;
                }
                else
                {
                    shooterAlpha = 0;
                    state = SO_DELETE;
                }



            }
            if (RandInt(0, 7) == 2)
                explosions.push_back(new Explosion(pos + Vector2D(RandDouble(20, (double)sprite->w+40), RandDouble(-10, sprite->w)), 1.0));
            SDL_SetAlpha(sprite, SDL_SRCALPHA, shooterAlpha);
            return;

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

void Sentry::Draw(CGameEngine *game, Runner *player)
{
    Vector2D draw = pos - player->GetDrawX() + START_POS;
    switch(state)
    {
        case SO_NEUTRAL:
        case SO_ALERT:
        case SO_DEAD:
            apply_surface(draw, sprite, game->GetScreen());
            break;
        case SO_SHOOT:
            apply_surface(draw, sprite, game->GetScreen());
            apply_surface(draw - Vector2D(SENTRY_BEAM_OFFSET.x, SENTRY_BEAM_OFFSET.y), sprite_beam, game->GetScreen(), &clip_beam[anim_beam.GetCurrentFrame()]);
            if (anim_beam.GetCurrentFrame() == anim_beam.maxFrames - 1)
            {
                state = SO_NEUTRAL;
                sound.Stop();
            }

            anim_beam.OnAnimate();
            break;
    }
    for (unsigned int i = 0; i < explosions.size(); ++i)
        explosions[i]->Draw(game, player->GetDrawX());
}

void Sentry::Kill(int k)
{
    hp -= k;
    for (unsigned int i = 0; i < 3; ++i)
        explosions.push_back(new Explosion(pos + Vector2D(RandDouble(20, (double)sprite->w+40), RandDouble(-10, sprite->w)), 1.0));
    if (hp <= 0)
    {
        state = SO_DEAD;
        sound.Stop();
    }

}

SDL_Rect* Sentry::GetColBox()
{
    SDL_Rect temp;
    temp.x = 0;
    temp.y = 0;
    temp.w = colBox.w;
    temp.h = colBox.h;
    return &temp;
}
void Sentry::Cleanup()
{
    SDL_FreeSurface(sprite);
    sound.Cleanup();
    for (unsigned int i = 0; i < explosions.size(); ++i)
    {
        explosions[i]->Cleanup();
        delete explosions[i];
        break;
    }
    explosions.clear();
}
