#include "../include/Collision.h"

bool CheckCol(Vector2D ppos, Vector2D pbox, Vector2D pvel, Vector2D bpos, Vector2D bbox)
{
    double pright = ppos.x + pbox.x;
    double pbot = ppos.y + pbox.y;
    double pleft = ppos.x;
    double ptop = ppos.y;

    double bright = bpos.x + bbox.x;
    double bbot = bpos.y + bbox.y;
    double bleft = bpos.x;
    double btop = bpos.y;


    if ((pbot+pvel.y < btop) || (ptop+pvel.y > bbot) || (pright+pvel.x < bleft)  || (pleft+pvel.x > bright))
        return false;

    return true;
}

Vector2D FixCol(Vector2D ppos, Vector2D pbox, Vector2D pvel, Vector2D bpos, Vector2D bbox, bool &onGround, bool &crashed, bool *bumpHead)
{
    //only need consider pbot-btop, pright-bleft, and diagonal cases
    double pright = ppos.x + pbox.x;
    double pbot = ppos.y + pbox.y;
    double pleft = ppos.x;
    double ptop = ppos.y;

    double bright = bpos.x + bbox.x;
    double bbot = bpos.y + bbox.y;
    double bleft = bpos.x;
    double btop = bpos.y;

    if (pright >= bleft && pleft <= bright && ptop+15 >= bbot)
    {
        *bumpHead = true;
        return Vector2D(0.0, bbot - (ptop + pvel.y));
    }
    else if (pright >= bleft && pleft <= bright && ptop < bbot) //vertical col
    {
        onGround = true;
        return Vector2D(0.0, btop - (pbot + pvel.y));
    }
    else if (pbot >= btop && ptop <= bbot && bright <= pleft) //hor
    {
        crashed = true;
        return Vector2D(0.0, 0.0);
    }
    else //assume diagonal condition
    {
        double slopeNormal = (ppos.y-ppos.y)/(ppos.x-ppos.y);
        double slopeVector = pvel.y/pvel.x;

        if (slopeVector > slopeNormal) //hor
        {
            crashed = true;
            return Vector2D(bleft - (pright + pvel.x), 0.0);
        }
        else
        {
            onGround = true;
            return Vector2D(0.0, btop - (pbot + pvel.y));
        }

    }

}
