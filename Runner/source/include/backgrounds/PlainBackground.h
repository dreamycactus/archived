#ifndef PLAINBACKGROUND_H
#define PLAINBACKGROUND_H

#include <vector>

#include "../SDL_Helper.h"
#include "../Background.h"
#include "../Runner.h"

using std::vector;
using std::string;

const int SCREEN_WIDTH = 1024;

class CGameEngine;

class PlainBackground : public Background
{
    public:
        PlainBackground(vector<string> temp, int drawHeight, int drawOffset, double sr);
        void Init();
        void Update(CGameEngine *game, Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();
    private:
        void Generate(BGBit &b);

        vector<SDL_Surface*> sprites;
        int drawHeight;
        vector<BGBit> bgBits;
        int drawOffset;
        int bgWidth;
        int numDraws;

};

#endif // PLAINBACKGROUND_H
