#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SDL_Helper.h"
#include "Vector2D.h"
#include "Thing.h"
#include "Runner.h"

#define O_ALIVE      0
#define O_DYING      1
#define O_DEAD       2

#define SO_NEUTRAL        2
#define SO_ALERT          0
#define SO_SHOOT          1
#define SO_DEAD           3
#define SO_DELETE         4

#define SHOOTER           0
#define CANNON            1
#define SENTRY            2
#define PLAIN             3

const int ALPHA_DECAY = 10;
class Runner;

class Obstacle
{
    public:
        virtual void Init() = 0;
        virtual void Update(CGameEngine *game, Runner *player) = 0;
        virtual void Draw(CGameEngine *game, Runner *player) = 0;
        virtual void Cleanup() = 0;
        virtual SDL_Rect* GetColBox() = 0;
        virtual void Kill(int k) = 0;
        Vector2D GetPos() { return pos; }
        int GetState() { return state; }


    protected:
        int state;
        Vector2D pos;
        SDL_Rect colBox;


};

#endif // OBSTACLE_H
