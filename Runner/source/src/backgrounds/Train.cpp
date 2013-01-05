#include "../../include/backgrounds/Train.h"
#include "../../include/screens/MainMenuScreen.h"
#include "../../include/screens/GameOverScreen.h"

using std::vector;

Train::Train()
{

}

void Train::Init(Vector2D p, int numTrams, double sr)
{
    tramCount = numTrams;
    pos = p;
    scrollRate = sr;
    trainSpeed = TRAIN_DEFAULT_SPEED;
    oldPx = 50;
    for (unsigned int i = 0; i < numTrams; ++i)
        trams.push_back(new Tram(Vector2D(pos.x + TRAM_WIDTH*i, pos.y - 2), scrollRate));
}

void Train::Update(CGameEngine *game, Vector2D p)
{
    unsigned int i;
    double la = (double)(trams.size() *  TRAM_WIDTH);
    double bla = trams[0]->GetPos().x - (p.x * scrollRate);
    if (bla < -la)
    {
        trainSpeed += 0.1;
    }
    else if (bla < 200 && trainSpeed < TRAIN_MAX_SPEED)
        trainSpeed += 0.05;
    else if (trainSpeed > TRAIN_DEFAULT_SPEED && bla > 0) //little fuzzy boundary
        trainSpeed -= 0.04;

    la = (double)(game->GetScreen()->w - TRAM_WIDTH);

    if (bla > la)
    {
        trams.back()->SetState(TRAM_SHAKE);
        trainSpeed = -10;
        oldPx = p.x;
    }
    else if ((bla < 0 || trams.size() == 1) && trams.back()->GetState() == TRAM_SHAKE)
    {
        trams.back()->SetState(TRAM_DEAD);
        trainSpeed = TRAIN_DEFAULT_SPEED;
    }

    pos.x += trainSpeed;


    if (trams.back()->GetState() == TRAM_DEAD)
    {
        trams.back()->Cleanup();
        delete trams.back();
        trams.pop_back();
    }
    for (i = 0; i < trams.size(); ++i)
    {
        trams[i]->Update(game, p);
        if (trams[i]->GetState() != TRAM_SHAKE)
            trams[i]->Move(Vector2D(trainSpeed, 0));

    }
    if (trams.empty())
        game->ChangeState(GameOverScreen::instance());
}

void Train::Draw(CGameEngine *game, Vector2D p)
{
    for (unsigned int i = 0; i < trams.size(); ++i)
        trams[i]->Draw(game, p);
}

void Train::Cleanup()
{
    for (unsigned int i = 0; i < trams.size(); ++i)
    {
        trams[i]->Cleanup();
        delete trams[i];
    }

    trams.clear();
}
