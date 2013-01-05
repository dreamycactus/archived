#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include "../SDL_Helper.h"
#include "../CGameEngine.h"



#include "../Runner.h"

#include "Tram.h"


using std::vector;

const int NUM_TRAMS = 5;
const Vector2D TRAIN_START_POS = Vector2D(0, 150);
const double TRAIN_ACCEL_POS = -200;
const double TRAIN_DEFAULT_SPEED = 3.8;
const double TRAIN_MAX_SPEED = 5.8;

class Train
{
    public:
        Train();
        void Init(Vector2D p, int numTrams, double sr);
        void Update(CGameEngine *game, Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();
    private:
        Vector2D pos;
        int tramCount;
        double scrollRate;
        double trainSpeed, oldPx;
        vector<Tram*> trams;

};

#endif // TRAIN_H
