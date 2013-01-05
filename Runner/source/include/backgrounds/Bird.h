#ifndef BIRD_H
#define BIRD_H

#include <vector>
#include <math.h>
#include "../SDL_Helper.h"
#include "../Vector2D.h"
#include "../CGameEngine.h"
#include "../CAnimation.h"

#define LEFT    0
#define RIGHT  1

#define STANDING  0
#define FLYING       1
#define HIDDEN       2

using std::vector;
using std::string;

const int BIRD_LEN = 15;
const int BIRD_OFFSET_Y = -11;


class CGameEngine;

class Bird
{
    public:
        Bird(string fileName, double dr, double rateSin, double rateX, double frameRate);
        void Init(Vector2D pos, int facing, double speed);
        void Update(Vector2D p, double sr);
        void Draw(CGameEngine *game, Vector2D p, double sr);
        void Cleanup();
        void Scan(Vector2D p);
        void Fly() { state = FLYING; }
    private:
        SDL_Surface* sprites;
        int facing;
        double detectionRange, t;
        Vector2D pos, origin;
        int state;
        CAnimation anim;
        CSoundEffect soundFlap;
        vector<SDL_Rect> clips;
        double speed, rateSin, rateX;

};

#endif // BIRD_H
