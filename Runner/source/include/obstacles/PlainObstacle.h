#ifndef PLAINOBSTACLE_H
#define PLAINOBSTACLE_H

#include <vector>
#include <string>
#include "../Obstacle.h"
#include "../SDL_Helper.h"
#include "../CAnimation.h"
#include "../Runner.h"
#include "../Collision.h"

#define DOG_MAN   0
#define CHAINSAW  1

using std::string;

class PlainObstacle : public Obstacle
{
    public:
        PlainObstacle(Vector2D p, string fileName, int type);
        void Init();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);
        void Cleanup() { SDL_FreeSurface(sprite); sound.Cleanup(); }
        void Kill(int k);
        SDL_Rect* GetColBox();
    private:
        SDL_Surface *sprite;
        double detectionRange;
        int shooterAlpha, dieLoop;
        CAnimation anim;
        SDL_Rect clips[2];

        CSoundEffect sound;

};

#endif // PLAINOBSTACLE_H
