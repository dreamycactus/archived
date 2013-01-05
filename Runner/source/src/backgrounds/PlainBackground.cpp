#include "../../include/backgrounds/PlainBackground.h"

using std::vector;
using std::string;


PlainBackground::PlainBackground(vector<string> temp, int drawHeight, int drawOffset, double sr)
{
    unsigned int i;
    for (i = 0; i < temp.size(); ++i)
    {
        sprites.push_back(load_image(temp[i]));
    }
    this->bgWidth = sprites[0]->w;
    this->drawHeight = drawHeight;
    this->drawOffset = drawOffset;
    this->scrollRate = sr;
    this->numDraws = (int) SCREEN_WIDTH/bgWidth + 2;

    for (i = 0; i < numDraws; ++i)
        bgBits.push_back(BGBit(drawHeight, 0));

    Init();

}

void PlainBackground::Init()
{
    pos = Vector2D(0, drawHeight);

}
void PlainBackground::Update(CGameEngine *game, Vector2D p)
{
    if ((p.x) * scrollRate - (pos.x + bgWidth) > 0)
    {
        pos.x += bgWidth;// - START_POS.x;
        for (unsigned int i = 0; i < bgBits.size()-1; ++i)
        {
            bgBits[i] = bgBits[i+1];
        }
        Generate(bgBits.back());
    }
}

void PlainBackground::Generate(BGBit &b)
{
    srand((unsigned)time(NULL));
    int floor = 0, ceil = sprites.size(), range = ceil-floor;
    b.index = rand() % range + floor;
    if (range != 0)
    floor = drawHeight; ceil = drawHeight + drawOffset; range = ceil-floor;
    if (range != 0)
        b.height = rand() % range + floor;
    else
        b.height = drawHeight;
}

void PlainBackground::Draw(CGameEngine *game, Vector2D p)
{
    Vector2D draw = Vector2D((pos.x) - p.x*scrollRate, 0);
    for (unsigned int i = 0; i < numDraws; ++i)
    {
        apply_surface(draw + Vector2D(bgWidth * i, bgBits[i].height), sprites[bgBits[i].index], game->GetScreen());
    }
}

void PlainBackground::Cleanup()
{
    for (unsigned int i = 0; i < sprites.size(); ++i)
    {
        SDL_FreeSurface(sprites[i]);
        sprites[i] = NULL;
    }
    sprites.clear();
    bgBits.clear();
}
