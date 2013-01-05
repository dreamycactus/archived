#ifndef COLLISION_H
#define COLLISION_H

#include "Vector2D.h"
#include <stdlib.h>

bool CheckCol(Vector2D ppos, Vector2D pbox, Vector2D pvel, Vector2D bpos, Vector2D bbox);

Vector2D FixCol(Vector2D ppos, Vector2D pbox, Vector2D pvel, Vector2D bpos, Vector2D bbox, bool &onGround, bool &crashed, bool *bumpHead);

#endif // COLLISIONH
