#include "../../include/obstacles/Shooter.h"



Shooter::Shooter(Vector2D pos)
{
    this->pos = pos;
    colBox.w = 50;
    colBox.h = 50;
    detectionRange = 700;
    attackRange = 400;
    weapDuration = 4;
    weapLevel = 16;
    shotOffset = 3;
    anims.SetFrameRate(0.3);
    anims.maxFrames = 2;
    anims.oscillate = false;
    clip_neutral.x = 0; clip_neutral.y = 0; clip_neutral.w = 50; clip_neutral.h = 50;
    clip_alert.x = 0; clip_alert.y = 50; clip_alert.w = 50; clip_alert.h = 50;
    clip_shoot[0] = clip_neutral; clip_shoot[0].y = 50;
    clip_shoot[1] = clip_neutral; clip_shoot[1].y = 100;
    Init();
}

void Shooter::Init()
{
    sprite_sheet = load_image("sprites/obstacles/shooter.png");
    weap_sprite_sheet = load_image("sprites/obstacles/shooter_bullet.png");
    laser_sprite = load_image("sprites/obstacles/shooter_laser.png");

    laserhumSound.load_sound("sounds/hum.wav");
    shootSound.load_sound("sounds/laser.wav");

    state = SO_NEUTRAL;
    dieLoop = 0;
    weapActive = false;
    weapElapsed = 0;
    bulletPos = Vector2D(pos.x, pos.y + weapLevel);
    trailAlpha = 255;
    shooterAlpha = 255;
}

void Shooter::Update(CGameEngine *game, Runner *player)
{
    int ptop = player->GetPos().y;
    int pbot = ptop + player->GetBox().y;

    if (state == SO_DEAD)
    {
        shooterAlpha -= 30;
        pos.x += 9;
        if (shooterAlpha < 0)
        {
            if (dieLoop <= MAX_DIE)
            {
                shooterAlpha = 230;
                ++dieLoop;
            }
            else
                shooterAlpha = 0;


        }

        SDL_SetAlpha(sprite_sheet, SDL_SRCALPHA, shooterAlpha);
        return;
    }


    if (pos.x - player->GetPos().x < detectionRange && state == SO_NEUTRAL && weapElapsed <= weapDuration)
    {
        state = SO_ALERT;
        laserhumSound.Play(-1);
    }
    //if enemy is within the attack range and hasn't fired yet
    if (pos.x - player->GetPos().x < attackRange && !weapActive && weapElapsed <= weapDuration)
    {
        weapActive = true; //fire
        shootSound.Play();
        laserhumSound.Stop();

    }


    //calculate if laser is on player or not
    if (weapLevel+pos.y > ptop && weapLevel+pos.y < pbot)
        laserEnd = player->GetPos().x;
    else
        laserEnd = player->GetPos().x - 500;

    //weapon hit duration
    if (weapElapsed > weapDuration)
    {
        weapActive = false;
        state = SO_NEUTRAL;
    }
    if (weapActive)
    {

        if (weapLevel + pos.y  > ptop && weapLevel + pos.y  < pbot && weapElapsed >= shotOffset) //if the bullet is on same level as player
            player->Stumble();
        bulletPos.x -= 200;
        state = SO_SHOOT;
        anims.OnAnimate();
        ++weapElapsed;
    }


}

void Shooter::Draw(CGameEngine *game, Runner *player)
{
    SDL_Rect c;
    //determine sprite for enemy
    switch(state)
    {
        case SO_NEUTRAL:
            c = clip_neutral;
            break;
        case SO_ALERT:
            c = clip_alert;
            break;
        case SO_SHOOT:
            c = clip_shoot[anims.GetCurrentFrame()];
            break;
        default: c = clip_neutral;
            break;
    }
    //draw enemy
    apply_surface(pos - player->GetDrawX() + START_POS, sprite_sheet, game->GetScreen(), &c);

    //draw laser
    double tempPos;
    if (state == SO_ALERT)
    {
        tempPos = pos.x;
        while (laserEnd < tempPos)
        {
            apply_surface(Vector2D(tempPos, bulletPos.y) - player->GetDrawX() + START_POS, laser_sprite, game->GetScreen());
            tempPos -= 16;
        }
    }
    //draw bullet
    if (weapActive)
        apply_surface(bulletPos - player->GetDrawX() + START_POS, weap_sprite_sheet, game->GetScreen());

}
void Shooter::Kill(int k)
{
    state = SO_DEAD;
    laserhumSound.Stop();
}
SDL_Rect* Shooter::GetColBox()
{
    SDL_Rect temp;
    temp.x = 17;
    temp.y = 10;
    temp.w = colBox.w;
    temp.h = colBox.h;
    return &temp;
}
void Shooter::Cleanup()
{
     SDL_FreeSurface(sprite_sheet);
     SDL_FreeSurface(weap_sprite_sheet);
     SDL_FreeSurface(laser_sprite);
}
