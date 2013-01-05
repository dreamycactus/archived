#include "../include/Glass.h"

Glass::Glass(Vector2D pos, Vector2D box) :  Thing(pos, box)
{
    this->pos = pos;
    this->box = box;
}

void Glass::Init()
{
    srand((unsigned)time(NULL));
    state = G_ALIVE;
    pane = load_image("sprites/pane.png");
    for (unsigned int i = 0; i < NUM_SHARDS; ++i)
        shards[i] = new Particle(Vector2D(pos.x, pos.y-50+i*8), Vector2D(0.0, 0.0), Vector2D(0, 0), Vector2D(-.05, GRAVITY.y));
}

void Glass::Update(CGameEngine *game, Runner *player)
{
    double floorx, rndx, ceilx, rangex, floory, rndy, ceily, rangey;

    unsigned int i;
    if (state == G_BREAK)
    {
        for (i = 0; i < NUM_SHARDS; ++i)
        {
            floorx = player->GetVelocity().x + 5; ceilx = player->GetVelocity().x + 30; rangex = (ceilx - floorx);
            rndx = floorx + (rangex * rand()) / (RAND_MAX + 1.0);
            floory = player->GetVelocity().y - 10, ceily= player->GetVelocity().y + 10;  rangey = (ceily - floory);
            rndy = floory + (rangey * rand()) / (RAND_MAX + 1.0);
            shards[i]->SetVelocity(Vector2D(rndx, rndy));
        }
        state = G_BROKEN;
    }
    else if (state == G_BROKEN)
    {
        for (i = 0; i < NUM_SHARDS; ++i)
        {
            shards[i]->Update(game, player);
        }
    }
}


void Glass::Draw(CGameEngine *game, Runner *player)
{
    if (state == G_ALIVE)
        apply_surface(pos - player->GetDrawX() + START_POS, pane, game->GetScreen());
    else if (state == G_BROKEN )
    {
        for (unsigned int i = 0; i < NUM_SHARDS; ++i)
        {
            shards[i]->Draw(game, player);
        }
    }

}

void Glass::Cleanup()
{
    SDL_FreeSurface(pane);
    for (unsigned int i = 0; i < NUM_SHARDS; ++i)
    {
        shards[i]->Cleanup();
        delete shards[i];
    }
}

void Glass::SetState(int state)
{
    if (state != G_BROKEN)
        this->state = state;
}
