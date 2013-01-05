#ifndef DOODAD_H
#define DOODAD_H

#include "CGameEngine.h"
#include "SDL_Helper.h"

using std::string;

class Doodad
{
    public:
        Doodad(string temp, Vector2D pos);
        void SetPos(Vector2D p);
        void Update(Vector2D p);
        void Draw(CGameEngine *game, Vector2D p);
        void Cleanup();
        bool Showing() { return show; }
    private:
        SDL_Surface *sprite;

        Vector2D pos;
        bool show;
};
#endif // DOODAD_H
