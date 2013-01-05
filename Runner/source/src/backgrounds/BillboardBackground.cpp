#include "../../include/backgrounds/BillboardBackground.h"

using std::vector;
using std::string;

BillboardBackground::BillboardBackground(vector<string> temp, vector< vector <double> > yLines, vector<Bounds> xBounds, int drawHeight, int drawOffset, double sr)
{
    unsigned int i;
    double mindr = 500, maxdr = 600;
    string fileName;

    srand((unsigned)time(NULL));
    for (i = 0; i < temp.size(); ++i)
    {
        sprites.push_back(load_image(temp[i]));
    }
    for (i = 0; i < NUM_BIRDS; ++i)
    {
        if (RandInt(0, 1) == 0)
            fileName = "sprites/backgrounds/bird_w.png";
        else
            fileName = "sprites/backgrounds/bird_b.png";

        birds.push_back(Bird(fileName, RandDouble(mindr, maxdr), RandDouble(3, 4.0), RandDouble(1.0, 3.0), RandDouble(0.0, 1.0)));
    }

    this->yLines = yLines;
    this->xBounds = xBounds;
    this->drawHeight = drawHeight;
    this->drawOffset = drawOffset;
    this->scrollRate = sr;

    Init();

}
void BillboardBackground::Init()
{
    pos = Vector2D(200, drawHeight);
    indexBill = 0;
    show = true;
}

void BillboardBackground::Update(CGameEngine *game, Vector2D p)
{


    unsigned int i;
    vector<Bird*>::iterator iter;

    if (pos.x + 600 - p.x < 0)
        show = false;
    if ((p.x) * scrollRate - (pos.x + sprites[indexBill]->w) > BILL_SPACING )
    {
        Generate(game->GetScreen()->w, p);
        show = true;
    }


    for (i  =  0; i < birds.size(); ++i)
    {
        birds[i].Update(p, scrollRate);
    }

}

void BillboardBackground::Generate(int w, Vector2D p)
{
    unsigned int i;
    /*Set billboard */

    pos.x = p.x * scrollRate + w; //correct billboard position to beyond scrollRate and player pos
    pos.y = RandDouble(drawHeight, drawHeight+drawOffset);
    indexBill = RandInt(0, sprites.size()-1);

    /*Spawn birds */
    int numBirds = RandInt(3, 15);
    int minSpeed = 2, maxSpeed = 4;
    int indexY;

    double posX, posY;
    int subNum = RandInt(0, NUM_BIRDS);
    for (i = 0; i < subNum; ++i)
    {
        indexY = RandInt(0, yLines[indexBill].size()-1);
        posX = RandDouble(xBounds[indexBill].min, xBounds[indexBill].max);
        posY = yLines[indexBill][indexY];
        birds[i].Init(Vector2D(posX, posY) + pos, RandInt(0,1),  RandDouble(minSpeed, maxSpeed));
    }
}
void BillboardBackground::Draw(CGameEngine *game, Vector2D p)
{
    Vector2D draw = Vector2D((pos.x) - p.x * scrollRate, pos.y);
    if (draw.x >= -sprites[indexBill]->w && draw.x <= game->GetScreen()->w)
        apply_surface(draw, sprites[indexBill], game->GetScreen());
    for (unsigned int i = 0; i < birds.size(); ++i)
        birds[i].Draw(game, p, scrollRate);
}
void BillboardBackground::Cleanup()
{
    unsigned int i ;
    for (i = 0; i < sprites.size(); ++i)
    {
        birds[i].Cleanup();
    }
    birds.clear();
    for (i = 0; i < sprites.size(); ++i)
    {
        SDL_FreeSurface(sprites[i]);
        sprites[i] = NULL;
    }
    sprites.clear();
    yLines.clear();
    xBounds.clear();
}
