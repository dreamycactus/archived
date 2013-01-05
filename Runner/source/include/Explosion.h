#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <vector>
#include "SDL_Helper.h"
#include "CGameEngine.h"
#include "CAnimation.h"

using std::vector;

class Explosion
{
    public:
        Explosion(Vector2D p, double sr);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup() { SDL_FreeSurface(sprite); sound.Cleanup(); }
        bool Done;
    private:
        Vector2D pos;
        CAnimation anim;
        SDL_Surface *sprite;
        vector<SDL_Rect> clips;
        double scrollRate;
        CSoundEffect sound;
};

#endif // EXPLOSION_H
