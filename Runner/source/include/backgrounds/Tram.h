#ifndef TRAM_H
#define TRAM_H

#define TRAM_NORMAL 0
#define TRAM_SHAKE  1
#define TRAM_DEAD   2

#include "../SDL_Helper.h"
#include "../CGameEngine.h"
#include "../Runner.h"
#include "../Explosion.h"

const int TRAM_WIDTH = 52;

using std::vector;

class Tram
{
    public:
        Tram(Vector2D p, double sr);
        void Update(CGameEngine *game, Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();
        void Move(Vector2D p);
        void SetState(int s) { state = s; }
        int GetState() { return state; }
        Vector2D GetPos() { return pos; }
    private:
        SDL_Surface *sprite;
        SDL_Surface *sprite_explo;
        vector<Explosion*> explosions;
        unsigned int maxExplosions, numExplosions;
        int state, oMax, oMin, shakeVel, alpha, dieLoop;
        double scrollRate;
        Vector2D pos;
};

#endif // TRAM_H
