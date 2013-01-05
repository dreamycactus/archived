#ifndef THING_H
#define THING_H

#include "Vector2D.h"

class Thing
{
    public:
        Thing();
        Thing(Vector2D pos, Vector2D box);

        Vector2D GetPos();
        Vector2D GetBox();

        void SetPos(Vector2D pos);
        void SetBox(Vector2D box);

    protected:
        Vector2D pos;
        Vector2D box;
    private:

};

#endif // THING_H
