#ifndef MENUENTRY_H
#define MENUENTRY_H


#include <string>
#include <vector>
#include "SDL_Helper.h"
#include "Vector2D.h"
#include "CGameEngine.h"



using namespace std;
class MenuEntry
{
    public:
        MenuEntry();
        MenuEntry(string text, CGameState *dest, Vector2D pos, SDL_Color color, TTF_Font *font);
        void SetSelect(bool s);
        void Update();
        void Draw(CGameEngine *game, TTF_Font *font);
        void Action(CGameEngine *game);
    protected:
    private:
        string text;
        int alpha;
        Vector2D pos;
        bool select;
        TTF_Font *font;
        CGameState *desti; //REMEMBER. this is bad code. because not all entries require a destination. e.g. turn off sound.
        SDL_Color color; //I'd like to use 'coloUr' here... but it'd be confusing
};

#endif // MENUENTRY_H
