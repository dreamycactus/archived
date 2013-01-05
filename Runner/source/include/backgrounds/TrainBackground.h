#ifndef TRAINBACKGROUND_H
#define TRAINBACKGROUND_H

#include <vector>
#include "../SDL_Helper.h"
#include "../Background.h"
#include "Train.h"

using std::vector;

class CGameEngine;

const double TRAIN_HEIGHT = 150;

class TrainBackground : public Background
{
    public:
        TrainBackground(double sr);
        void Init();
        void Update(CGameEngine *game, Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();
    private:
        SDL_Surface *tempT;
        SDL_Surface *tracks;
        SDL_Surface *station;
        Train train;
        double stationPosX, tracksPosX;

};

#endif // TRAINBACKGROUND_H
