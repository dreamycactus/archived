#include "../../include/obstacles/Cannon.h"

Cannon::Cannon(Vector2D pos)
{
    unsigned int i, AF = 6, SF = 5;

    this->pos = pos;
    colBox.w = 120;
    colBox.h = 100;
    detectionRange = 850;
    attackRange = 520;
    shotOffset = 2;

    weapDuration = 6;
    weapLevelMin = 20;
    weapLevelMax = 80;

    anims[SO_ALERT].SetFrameRate(0.3);
    anims[SO_ALERT].maxFrames = AF;
    anims[SO_SHOOT].SetFrameRate(0.3);
    anims[SO_SHOOT].maxFrames = SF;

    anim_beam.SetFrameRate(5);
    anim_beam.maxFrames = 5;

    sprite = load_image("sprites/obstacles/enemy_cannon.png");
    sprite_beam = load_image("sprites/obstacles/cannon_blast.png");

    clip_neutral.x = 0; clip_neutral.y = 0; clip_neutral.w = sprite->w; clip_neutral.h = sprite->w;

    for (i = 0; i < AF; ++i)
    {
        clip_alert[i].x = 0;
        clip_alert[i].y = i * sprite->w;
        clip_alert[i].w = sprite->w;
        clip_alert[i].h = sprite->w;
    }
    for (i = 0; i < SF; ++i)
    {
        clip_shoot[i].x = 0;
        clip_shoot[i].y = (i+6) * sprite->w;
        clip_shoot[i].w = sprite->w;
        clip_shoot[i].h = sprite->w;

        clip_beam[i].x = 0;
        clip_beam[i].y = i * 85;
        clip_beam[i].w = 584;
        clip_beam[i].h = 85;

    }
    Init();
}

void Cannon::Init()
{
    state = SO_NEUTRAL;
    dieLoop = 0;
    weapActive = false;
    weapElapsed = 0;
    shooterAlpha = 255;
    hp = 2;
    soundRev.load_sound("sounds/phaser.wav");
    soundFire.load_sound("sounds/revFLaser.wav");
    shot = false;
}

void Cannon::Update(CGameEngine *game, Runner *player)
{
    switch(state)
    {
        case SO_NEUTRAL:
            if (pos.x - player->GetPos().x < detectionRange)
            {
                if (!shot)
                {
                    state = SO_ALERT;
                    soundRev.Play(-1);
                }

            }
            break;
        case SO_ALERT:
            if (pos.x - player->GetPos().x < attackRange)
            {
                state = SO_SHOOT;
                shot = true;
                soundRev.Stop();
                soundFire.Play();
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
            shooterAlpha -= 30;
            pos.x += 1;
            if (shooterAlpha < 0)
            {
                if (dieLoop <= 2)
                {
                    shooterAlpha = 230;
                    ++dieLoop;
                    if (RandInt(0, 6) == 2)
                        explosions.push_back(new Explosion(pos + Vector2D(RandDouble(20, (double)sprite->w+40), RandDouble(-10, sprite->w)), 1.0));
                }
                else
                {
                    shooterAlpha = 0;
                    state = SO_DELETE;
                }



            }

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

void Cannon::Draw(CGameEngine *game, Runner *player)
{
    Vector2D draw = pos - player->GetDrawX() + START_POS;
    switch(state)
    {
        case SO_ALERT:
            apply_surface(draw, sprite, game->GetScreen(), &clip_alert[anims[SO_ALERT].GetCurrentFrame()]);
            anims[SO_ALERT].OnAnimate();
            break;
        case SO_SHOOT:
            apply_surface(draw, sprite, game->GetScreen(), &clip_shoot[anims[SO_SHOOT].GetCurrentFrame()]);
            apply_surface(draw - Vector2D(CANNON_BEAM_OFFSET.x, CANNON_BEAM_OFFSET.y), sprite_beam, game->GetScreen(), &clip_beam[anim_beam.GetCurrentFrame()]);
            if (anim_beam.GetCurrentFrame() == anim_beam.maxFrames - 1)
                state = SO_NEUTRAL;
            anims[SO_SHOOT].OnAnimate();
            anim_beam.OnAnimate();
            break;
        case SO_DEAD:
        case SO_NEUTRAL:
            apply_surface(draw, sprite, game->GetScreen(), &clip_neutral);
            break;
    }
    for (unsigned int i = 0; i < explosions.size(); ++i)
        explosions[i]->Draw(game, player->GetDrawX());
}

void Cannon::Kill(int k)
{
    hp -= k;
    for (unsigned int i = 0; i < 5; ++i)
        explosions.push_back(new Explosion(pos + Vector2D(RandDouble(20, (double)sprite->w+40), RandDouble(-10, (double)sprite->w)), 1.0));
    if (hp <= 0)
    {
        state = SO_DEAD;
        soundFire.Stop();
        soundRev.Stop();
    }

}

SDL_Rect* Cannon::GetColBox()
{
    SDL_Rect temp;
    temp.x = 0;
    temp.y = 0;
    temp.w = sprite->w;
    temp.h = sprite->w;
    return &temp;
}
void Cannon::Cleanup()
{
     SDL_FreeSurface(sprite);
     soundRev.Cleanup();
     soundFire.Cleanup();
    for (unsigned int i = 0; i < explosions.size(); ++i)
    {
        explosions[i]->Cleanup();
        delete explosions[i];
        break;
    }
    explosions.clear();
}
