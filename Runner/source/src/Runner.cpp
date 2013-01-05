#include "../include/Runner.h"
#include <math.h>
#include "../include/screens/GameOverScreen.h"

const int nums[NUM_ACTIONS] = {16, 7, 9, 16, 8, 8};

int Other(int mode)
{
    if (mode == GRAVE)
        return MARIA;
    return GRAVE;
}

Runner::Runner()
{
    unsigned int i, j;
    const int SPRITE_LEN = 100;
    SDL_Rect tempR;
    std::vector<SDL_Rect> tempV;
    tempR.w = SPRITE_LEN;
    tempR.h = SPRITE_LEN;
    for (i = 0; i < NUM_ACTIONS; ++i)
    {
        tempR.x = i*SPRITE_LEN;
        for (j = 0; j < nums[i]; ++j)
        {
            tempR.y = j*SPRITE_LEN;
            tempV.push_back(tempR);
        }
        clips.push_back(tempV);
        tempV.clear();
    }
    for (i = 0; i < NUM_ACTIONS; ++i)
    {
        anims[i].maxFrames = nums[i];
        collisionBox[i].x = 45;
        collisionBox[i].y = 50;
        collisionBox[i].w = 10;
        collisionBox[i].h = 40;
    }
    tempR.x = 0;
    tempR.y = 0;
    tempR.w = 10;
    tempR.h = 22;
    swordClip.push_back(tempR);
    tempR.y = 22;
    swordClip.push_back(tempR);


    swap.maxFrames = nums[A_SWAP];
    collisionBox[A_CROUCH].y = 75;
    collisionBox[A_CROUCH].h = 15;
    collisionBox[A_JUMP].y = 60;
    collisionBox[A_JUMP].h = 30;


    gunRange = { 1020, 100 };
    slideFriction[GRAVE] = 0.025; //different coefficients for each char
    slideFriction[MARIA] = 0.01;
    jumpFactor[GRAVE] = 10; //jump height
    jumpFactor[MARIA] = 11;
    jumpTime[GRAVE] = 4;
    jumpTime[MARIA] = 3;
    jumpLen[GRAVE] = 4; //jump horizontal speed boost
    jumpLen[MARIA] = 10;


        //set clips
    tempRect.x = 0; tempRect.y = 0;
    tempRect.w = 35; tempRect.h = 9;
}

void Runner::Init()
{
    grave_sprite = load_image( "sprites/grave.png" );
    maria_sprite = load_image( "sprites/maria.png" );
    bullet_sprite = load_image( "sprites/runner_bullet.png" );
    sword_sprite = load_image( "sprites/swordslash.png" );
    temp = load_image("sprites/temp.png");
    soundHit.load_sound("sounds/doom.wav");

    //Initialize movement variables
    velocity = Vector2D(12, 0.0);
    pos = START_POS;
    pos.y = 70;
    state = S_RUN;
    tempAnchor = Vector2D(0, 0);
    tempPosG = Vector2D(0, 0);
    tempPosM = Vector2D(0, 0);


    anims[A_RUN].SetFrameRate(0);
    anims[A_JUMP].SetFrameRate(.3);
    anims[A_JUMP].frameTransStart = 5;
    anims[A_SWAP].SetFrameRate(3);
    anims[A_CROUCH].frameTransStart = 4;
    anims[A_CROUCH].SetFrameRate(0.3);
    anims[A_SHOOT].frameTransStart = 4;
    anims[A_SHOOT].SetFrameRate(0);
    animSword.maxFrames = 2;
    animSword.SetFrameRate(3);


    mode = RandInt(0, 1);
    showChar[mode] = true;
    showChar[Other(mode)] = false;
    charState[GRAVE] = C_OK;
    charState[MARIA] = C_OK;
    swapTimer = SWAP_TIME;

    onGround = false;
    crashed = false;
    swapping = false;

    dazeTimer[GRAVE] = 0;
    dazeTimer[MARIA] = 0;
    invTimer = 0;
    jumpTimer = 0;
    mariaSwordTimer = SWORD_INVINCIBLE + 1;


    SetAction(A_RUN);
    for (unsigned int i = 0; i < NUM_ACTIONS; ++i)
    {
        action[i] = true;
        animTransDone[i] = true;
    }
    GAMEOVER = false;

    /* Load Sounds */

    int i, j;
    vector<CSoundEffect> tempS;
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            tempS.push_back(CSoundEffect());
        }
        soundEffects.push_back(tempS);
        tempS.clear();
    }
    soundEffects[GRAVE][SOUND_JUMP ].load_sound("sounds/grave_jump.wav");
    soundEffects[GRAVE][SOUND_SHOOT].load_sound("sounds/grave_shoot.wav");
    soundEffects[GRAVE][SOUND_SLIDE].load_sound("sounds/grave_slide.wav");
    soundEffects[GRAVE][SOUND_SWAP].load_sound("sounds/grave_swap.wav");

    soundEffects[MARIA][SOUND_JUMP ].load_sound("sounds/maria_jump.wav");
    soundEffects[MARIA][SOUND_SHOOT].load_sound("sounds/maria_shoot.wav");
    soundEffects[MARIA][SOUND_SLIDE].load_sound("sounds/maria_slide.wav");
    soundEffects[MARIA][SOUND_SWAP].load_sound("sounds/maria_swap.wav");


    soundEffects.push_back(tempS);
    for (unsigned int i = 0; i < tempS.size(); ++i)
        tempS[i].Cleanup();
    tempS.clear();

}



void Runner::HandleInput()
{
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if (!keystates[SDLK_DOWN])
        action[A_CROUCH] = true;
    if (!keystates[SDLK_UP])
        action[A_JUMP] = true;
    if (!keystates[SDLK_LEFT])
        action[A_SWAP] = true;
    if (!keystates[SDLK_RIGHT])
        action[A_SHOOT] = true;

    bool animDone = true;
    for (unsigned int i = 0; i < NUM_ACTIONS; ++i)
    {
        if (!animTransDone[i])
            animDone = false;
    }

    switch(state)
    {
        case S_STUMBLE:
            if (keystates[SDLK_LEFT] && action[A_SWAP] && onGround)
            {
                Swap();
            }

            break;
        case S_RUN:
            if (keystates[SDLK_DOWN] && action[A_CROUCH] && velocity.x > 10 && animDone)
            {
                soundEffects[mode][SOUND_SLIDE].Play();
                action[A_CROUCH] = false;
                animTransDone[A_CROUCH] = false;
                SetState(S_CROUCH);
                SetAction(A_CROUCH);

            }
            else if (keystates[SDLK_UP] && action[A_JUMP] && animDone)
            {
                soundEffects[mode][SOUND_JUMP].Play();
                velocity.x += jumpLen[mode];
                SetState(S_JUMP_START);
                action[A_JUMP] = false;
                animTransDone[A_JUMP] = false;
                SetAction(A_JUMP);

            }
            else if (keystates[SDLK_RIGHT] && action[A_SHOOT] && animDone)
            {
                soundEffects[mode][SOUND_SHOOT].Play();
                if (mode == MARIA)
                    mariaSwordTimer = 0;
                SetState(S_SHOOT);
                action[A_SHOOT] = false;
                animTransDone[A_SHOOT] = false;
                SetAction(A_SHOOT);

            }
            else if (keystates[SDLK_LEFT] && action[A_SWAP] && animDone && currentAction != A_SWAP && charState[Other(mode)] == C_OK)
            {
                Swap();
            }

            break;
        case S_JUMP_START:
            if (!keystates[SDLK_UP]&& state != S_JUMP_FINISH)
            {
                SetState(S_JUMP_FINISH);
            }
            break;
        case S_CROUCH:
            if (!keystates[SDLK_DOWN] || velocity.x < 5)
            {
                SetState(S_RUN);
                SetAction(A_RUN);
            }
            break;
        case S_SHOOT:
            if (!keystates[SDLK_RIGHT] && animDone)
            {
                SetState(S_RUN);
                SetAction(A_RUN);
            }
            break;
        case S_JUMP_FINISH:
        default:
            break;
    }

}


void Runner::Update(CGameEngine* game, Building *lastBuilding, Obstacle *enemy)
{

    ++invTimer;
    if (mode == MARIA)
    {
        ++mariaSwordTimer;
        if (mariaSwordTimer > SWORD_INVINCIBLE)
            mariaSwordTimer = SWORD_INVINCIBLE + 1;
    }
    if (swapTimer < SWAP_TIME)
        ++swapTimer;

    //handle dazed mode
    if (charState[GRAVE] == C_DEAD && charState[MARIA] == C_DEAD)
    {
        GAMEOVER = true;
    }


    if (!onGround && state != S_JUMP_START && state != S_JUMP_FINISH && state != S_STUMBLE)//fell off
    {
        SetState(S_JUMP_FINISH);
        SetAction(A_JUMP);

    }
    else if (state == S_JUMP_FINISH && onGround) //landed
    {
        jumpTimer = 0;
        velocity.x -= jumpLen[mode] * 1.3;
        if (velocity.x <= 0)
            velocity.x = 0;
        onGround = true;
        SetState(S_RUN);
        SetAction(A_RUN);
 //       anims[currentAction].Reset();
    }
    else if (state == S_SHOOT)
    {
        int dmg = mode + 1;
        if (enemy != NULL && anims[A_SHOOT].GetCurrentFrame() == 7)
        {
            enemy->Kill(dmg);
        }
    }
    else if (swapping) //swap character
    {
        swap.OnAnimate();

        showChar[mode] = true;
        showChar[Other(mode)] = false;

        if (miniTimer < 18)
        {
            ++miniTimer;
        }

        if (miniTimer == 18)
        {
            swapping = false;
            miniTimer = 0;


            tempPosM = Vector2D(0, 0);
            tempPosG = Vector2D(0, 0);

        }
        else
        {
            if (mode == GRAVE)
                tempPosM = pos - tempAnchor; //something to do with position
            else
                tempPosG = pos - tempAnchor;
        }
    }
    if (charState[mode] != C_OK && charState[Other(mode)] == C_OK) //respawn
    {
        if (pos.y > 480)
        {
            showChar[mode] = false;
            pos.x = lastBuilding->GetColPos().x;
            pos.y = lastBuilding->GetColPos().y - collisionBox[A_RUN].h-60;
            velocity.y = 0;
            velocity.x = 10;
            SetState(S_RUN);
            SetAction(A_RUN);
            if (mode == GRAVE) mode = MARIA;
            else mode = GRAVE;
            showChar[mode] = true;
        }
    }
    for (unsigned int i = 0; i < 2; ++i)
    {
        if (dazeTimer[i] > 0)
            --dazeTimer[i];
        if (dazeTimer[i] == 0 && charState[i] != C_DEAD && charState[i] != C_OK)
        {
            charState[i] = C_OK;
            if (currentAction == A_STUMBLE)
                currentAction = A_RUN;
            if (state == S_STUMBLE)
                state = S_RUN;
        }
    }

    Move();


    if (anims[A_JUMP].GetCurrentFrame() == anims[A_JUMP].maxFrames - 1)
    {
        animTransDone[A_JUMP] = true;
        anims[A_JUMP].Reset();
        anims[A_RUN].Reset();
        SetState(S_RUN);
        SetAction(A_RUN);
    }
    else if (anims[A_SHOOT].GetCurrentFrame() == anims[A_SHOOT].maxFrames -1)
    {
        animTransDone[A_SHOOT] = true;
        anims[A_SHOOT].Reset();
        anims[A_RUN].Reset();
        SetState(S_RUN);
        SetAction(A_RUN);
    }
    else if (anims[A_CROUCH].GetCurrentFrame() == anims[A_CROUCH].maxFrames -1)
    {
        animTransDone[A_CROUCH] = true;
        anims[A_CROUCH].Reset();
        anims[A_RUN].Reset();
        SetState(S_RUN);
        SetAction(A_RUN);
    }
    else if (anims[A_SWAP].GetCurrentFrame() == anims[A_SWAP].maxFrames -1)
    {

    }

    anims[currentAction].OnAnimate();
    switch (state)
    {

        case S_JUMP_START:
        case S_JUMP_FINISH:
            if (anims[currentAction].GetCurrentFrame() == 3)
                anims[currentAction].Hold(true);
            break;
        case S_CROUCH:
            if (anims[currentAction].GetCurrentFrame() == 4)
                anims[currentAction].Hold(true);
            break;
        case S_STUMBLE:
            if (anims[currentAction].GetCurrentFrame() == anims[currentAction].maxFrames - 1)
                anims[currentAction].Hold(true);
            break;
        default: break;
    }


}

void Runner::Draw(CGameEngine* game)
{
    SDL_Rect clipG;
    SDL_Rect clipM;
    //Show the stick figure on the screen

    if (currentAction == A_RUN)
    {
        if (!animTransDone[A_JUMP])
        {
            anims[A_JUMP].Hold(false);
            clipG = clipM = clips[A_JUMP][anims[A_JUMP].GetCurrentFrame()];
            SetAction(A_JUMP);
        }

        else if (!animTransDone[A_CROUCH])
        {
            anims[A_CROUCH].Hold(false);
            clipG = clipM = clips[A_CROUCH][anims[A_CROUCH].GetCurrentFrame()];
            SetAction(A_CROUCH);
        }
        else if (!animTransDone[A_SHOOT])
        {
            clipG = clipM = clips[A_SHOOT][anims[A_SHOOT].GetCurrentFrame()];
            SetAction(A_SHOOT);
        }
        else
            clipG = clipM = clips[currentAction][anims[currentAction].GetCurrentFrame()];
    }

    else
        clipG = clipM = clips[currentAction][anims[currentAction].GetCurrentFrame()];


    if (state == S_SHOOT && anims[A_SHOOT].GetCurrentFrame() >= 7 && anims[A_SHOOT].GetCurrentFrame() <= 9 && mode == GRAVE)
        apply_surface(START_POS+GetDrawY()+Vector2D(75, 55), bullet_sprite, game->GetScreen());
    if (state == S_SHOOT && anims[A_SHOOT].GetCurrentFrame() >= 3 && anims[A_SHOOT].GetCurrentFrame() <= 12 && mode == MARIA)
    {
        apply_surface(START_POS+GetDrawY()+Vector2D(85, 52), sword_sprite, game->GetScreen(), &swordClip[animSword.GetCurrentFrame()]);
        animSword.OnAnimate();
    }


    if (showChar[GRAVE])
        apply_surface(START_POS+GetDrawY()-tempPosG, grave_sprite, game->GetScreen(), &clipG);
    if (showChar[MARIA])
        apply_surface(START_POS+GetDrawY()-tempPosM, maria_sprite, game->GetScreen(), &clipM);
    if (swapping)
    {
        if (mode == GRAVE)
            apply_surface(START_POS+tempAnchor-GetDrawX(), maria_sprite, game->GetScreen(), &clips[A_SWAP][swap.GetCurrentFrame()]);
        else if (mode == MARIA)
            apply_surface(START_POS+tempAnchor-GetDrawX(), grave_sprite, game->GetScreen(), &clips[A_SWAP][swap.GetCurrentFrame()]);
    }
    //apply_surface(Vector2D(START_POS.x, 241), temp, game->GetScreen(), &tempRect);
    //apply_surface(START_POS+GetPosY()+ Vector2D(10, 38), temp, game->GetScreen(), &tempRect);

}

Vector2D Runner::NextSpeed()
{
    if (state != S_RUN && state != S_CROUCH)
        return Vector2D(0.0, 0.0);

    Vector2D n_vel = velocity;
    if (state == S_CROUCH)
        return (Vector2D(-slideFriction[mode]*velocity.x, 0.0));

    n_vel.y = 0.0;
    if (n_vel.x < MAX_SPEED/4)
        n_vel.x = 4*STEP;
    else if (n_vel.x < MAX_SPEED/2)
        n_vel.x = .9*STEP;
    else if (n_vel.x < MAX_SPEED*2/3)
        n_vel.x = .45*STEP;
    else if (n_vel.x < MAX_SPEED*3/4)
        n_vel.x = 0.4*STEP;
    else
        n_vel.x = 0;

    return n_vel;
}

void Runner::Move()
{
    switch(state)
    {
        case S_JUMP_START:
            Jump();
            break;
        case S_STUMBLE:
            velocity.x -= 0.06*velocity.x;
            break;
        default: break;
    }
    if (charState[mode] == C_DEAD)
        velocity = Vector2D(0, 30);


    pos += velocity;
}


bool Runner::Jump()
{
    //piecewise jump function for better air control
    double JUMP_LIMIT = -(0.3 * velocity.x + jumpFactor[mode]);//jump max speed depends slightly on x-speed

    if (jumpTimer < jumpTime[mode])
        velocity.y -= jumpFactor[mode]; //these values must be 'more' than gravity, or else jump may never end
    else
        SetState(S_JUMP_FINISH);

    ++jumpTimer;
    return true;

}

void Runner::Swap()
{
    if ((mode == MARIA && charState[GRAVE] != C_OK) || (mode == GRAVE && charState[MARIA] != C_OK))
        return;
    if (swapTimer < SWAP_TIME)
        return;

    soundEffects[mode][SOUND_SWAP].Play();
    swapTimer = 0;
    miniTimer = 0;
    invTimer = 0;
    swapping = true;
    anims[A_RUN].Reset();
    action[A_SWAP] = false;

    SetState(S_RUN);
    SetAction(A_RUN);

    if (mode == GRAVE)
        mode = MARIA;
    else
        mode = GRAVE;

    tempAnchor = pos;
    swap.Reset();
}

void Runner::Stumble()
{
    if (invTimer < INVINCIBLE_TIME || (mariaSwordTimer < SWORD_INVINCIBLE && mode == MARIA))
        return;
    if (!soundHit.IsPlaying())
        soundHit.Play();
    for (unsigned int i = 0; i < NUM_ACTIONS; ++i)
        animTransDone[i] = true;
    SetAction(A_STUMBLE);
    SetState(S_STUMBLE);
    if (charState[mode] != C_DEAD)
        charState[mode] = C_DAZE;
    dazeTimer[mode] = DAZE_TIME;
    anims[A_STUMBLE].Reset();
}
void Runner::SetOnGround(bool b)
{
    onGround = b;
}

void Runner::SetCrashed(bool b)
{
    if (b)
        charState[mode] = C_DEAD;
}

void Runner::Cleanup()
{
    SDL_FreeSurface(grave_sprite);
    SDL_FreeSurface(maria_sprite);
    SDL_FreeSurface(poof_sprite);
    SDL_FreeSurface(bullet_sprite);
    SDL_FreeSurface(sword_sprite);
    SDL_FreeSurface(temp);
    for (unsigned int i = 0; i < soundEffects.size(); ++i)
        for (unsigned int j = 0; j < soundEffects[i].size(); ++j)
            soundEffects[i][j].Cleanup();
    soundEffects.clear();
}

void Runner::Reset()
{
    Init();
}

Vector2D Runner::GetVelocity()
{
    return velocity;
}

int Runner::GetState()
{

    return state;
}

void Runner::SetAction(int action)
{
    currentAction = action;
    box = Vector2D(collisionBox[currentAction].w, collisionBox[currentAction].h);
}
Vector2D Runner::GetPos()
{
    return Vector2D(pos.x + collisionBox[currentAction].x, pos.y + collisionBox[currentAction].y);
}
Vector2D Runner::GetDrawX()
{
    return Vector2D(pos.x, 0.0);
}


Vector2D Runner::GetDrawY()
{
    return Vector2D(0.0, pos.y);
}

void Runner::SetState(int state)
{
    if (this->state != S_DEAD)
        this->state = state;
}

void Runner::SetVelocity(Vector2D velocity)
{
    this->velocity = velocity;
}



