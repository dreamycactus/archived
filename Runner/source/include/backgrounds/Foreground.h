#ifndef FOREGROUND_H
#define FOREGROUND_H


#include <vector>

#include "../SDL_Helper.h"
#include "../Collision.h"
#include "../Background.h"
#include "../Runner.h"

#define BG_TANK        0
#define BG_TANK_LEAK   1
#define BG_EVA         2


using std::vector;
using std::string;


class CGameEngine;

class Foreground : public Background
{
    public:
        Foreground(int drawO, double sr);
        void Init() {}
        void Update(CGameEngine *game, Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();
    private:
        void Generate(BGBit &b);

        vector<SDL_Surface*> sprites;
        vector<CAnimation> anims;
        vector< vector<SDL_Rect> > clips;
        vector<Vector2D> pos;
        vector<SDL_Rect> box;
        int drawOffset;

};

#endif // FOREGROUND_H
