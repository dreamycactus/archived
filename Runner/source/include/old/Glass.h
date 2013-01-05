#ifndef GLASS_H
#define GLASS_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "SDL_Helper.h"
#include "Thing.h"
#include "Particle.h"
#include "Runner.h"


#define G_ALIVE            1
#define G_BREAK            2
#define G_BROKEN           3

const int NUM_SHARDS = 25;

class CGameEngine;
class Level;

class Glass : public Thing
{
    public:
        Glass(Vector2D pos, Vector2D box);
        void Init();
        void Cleanup();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);

        void SetState(int state);

        friend class Level;
    protected:
    private:
        int state;
        bool once;
        SDL_Surface *pane;
        Particle *shards[NUM_SHARDS];
};

#endif // GLASS_H
