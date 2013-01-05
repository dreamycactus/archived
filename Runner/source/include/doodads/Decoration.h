#ifndef DECORATION_H
#define DECORATION_H

#include "../Thing.h"
#include "../Runner.h"

class Decoration : public Thing
{
    public:
        Decoration(Vector2D pos, SDL_Surface *sprite);
        void Draw(CGameEngine *game, Runner *player);
        void Cleanup();
    private:
        SDL_Surface *sprite;

};

#endif // DECORATION_H
