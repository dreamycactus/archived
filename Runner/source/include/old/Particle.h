#ifndef PARTICLE_H
#define PARTICLE_H

#include "Thing.h"
#include "SDL_Helper.h"
#include "Runner.h"

#define ALIVE            1
#define GONE             2

class CGameEngine;

class Particle : public Thing
{
    public:
        Particle();
        Particle(Vector2D pos, Vector2D box, Vector2D velocity, Vector2D acceleration);

        void SetVelocity(Vector2D velocity);

        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);
        void Cleanup();
    protected:
    private:
        Vector2D velocity;
        int lifeTotal;
        int lifeElapsed;
        int frame;
        int state;

        Vector2D acceleration;

        SDL_Surface *sprite_sheet;
        SDL_Rect clip1[4];
};

#endif // PARTICLE_H
