#ifndef BILLBOARDBACKGROUND_H
#define BILLBOARDBACKGROUND_H

#include <vector>
#include "../SDL_Helper.h"
#include "../Background.h"
#include "Bird.h"

const int BILL_SPACING = 1500;
const int NUM_BIRDS = 20;

using std::vector;
using std::string;

class Bounds
{
    public:
        Bounds(int min, int max) { this->min = min; this->max = max; }
        double min, max;
};

class CGameEngine;

class BillboardBackground : public Background
{
    public:
        BillboardBackground(vector<string> temp, vector< vector <double> > yLines, vector<Bounds> xBounds, int drawHeight,  int drawOffset, double sr);
        void Init();
        void Update(CGameEngine *game, Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();

    private:
        void Generate(int w, Vector2D p);
        vector<Bird> birds;
        vector<SDL_Surface*> sprites;
        vector< vector<double> > yLines;//bird y spawn locations
        vector<Bounds> xBounds; //bird x spawn bounds
        int drawHeight, drawOffset, indexBill;
        bool show;
};

#endif // BILLBOARDBACKGROUND_H
