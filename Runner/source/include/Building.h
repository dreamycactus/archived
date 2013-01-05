#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include <string>
#include "Vector2D.h"
#include "Runner.h"

#define GIRDER       0

const int BLOCK_WIDTH = 62;

class CGameEngine;
class Runner;

using std::vector;

class Building
{
    public:
        Building(){}
        Building(Vector2D pos, int num, double slevel, int np, std::string spriteFiles);
        void Draw(CGameEngine *game, Runner *player);
        void Cleanup();
        Vector2D GetDrawPos();
        Vector2D GetColPos();
        Vector2D GetBox();

    private:
        SDL_Surface *sprite;
        SDL_Surface *whole;
        vector<SDL_Rect> clips;
        int numPieces;
        double surfaceLevel;
        Vector2D pos;
        Vector2D box;
        int numMiddles;
        vector<int> blocks;

};

#endif // BUILDING_H
