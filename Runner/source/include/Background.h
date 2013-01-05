#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "CGameEngine.h"
#include "Vector2D.h"


class BGBit
{
    public:
        BGBit(int h, int i)
        {
            height = h;
            index = i;
        }
        BGBit& operator=(const BGBit &rhs)
        {
            this->height = rhs.height;
            this->index = rhs.index;
            return *this;
        }
        int height, index;
};

class Background
{
    public:
        virtual void Init() = 0;
        virtual void Update(CGameEngine *game, Vector2D pos) = 0;
        virtual void Draw(CGameEngine *game, Vector2D pos) = 0;
        virtual void Cleanup() = 0;
        Vector2D GetDrawPos() { return pos; }
        
    protected:
        Vector2D pos;
        double scrollRate;
};

#endif // BACKGROUND_H
