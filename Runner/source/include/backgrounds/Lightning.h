#ifndef LIGHTNING_H
#define LIGHTNING_H

#include <vector>
#include <string>
#include "../CGameEngine.h"
#include "../Vector2D.h"
#include "../CAnimation.h"
#include "../SDL_Helper.h"

using std::vector;

class Lightning
{
    public:
        Lightning();
        void Update(Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Flash(CGameEngine *game);
        void Cleanup();
    private:
        Vector2D pos;
        vector<SDL_Surface*> sprites;
        double nextStrike;
        int thunderTime;
        CAnimation anim;
        CSoundEffect sound;
        vector<SDL_Rect> clips;
        bool showLight, showFlash, thundered;
        int flashAlpha, indexSprite, oscillateMax, oscillateCount, flashDelta;
};

#endif // LIGHTNING_H
