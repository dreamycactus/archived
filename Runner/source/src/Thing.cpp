#include "../include/Thing.h"

Thing::Thing()
{
    //ctor
}


Thing::Thing(Vector2D pos, Vector2D box)
{
    this->pos = pos;
    this->box = box;
}

Vector2D Thing::GetPos()
{
    return pos;
}

Vector2D Thing::GetBox()
{
    return box;
}

void Thing::SetPos(Vector2D pos)
{
    this->pos = pos;
}
void Thing::SetBox(Vector2D box)
{
    this->box = box;
}
