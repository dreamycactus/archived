#ifndef MENU_H
#define MENU_H

#include "MenuEntry.h"

using namespace std;

class Menu
{
    public:
        Menu(){}
        virtual void HandleInput(CGameEngine *game) = 0;
        virtual void SelectEntry(int entryIndex) = 0;
        virtual void Cancel() = 0;
        virtual void Update() = 0;
        virtual void Draw(CGameEngine *game) = 0;
        virtual void Cleanup() = 0;
        virtual void AddEntry(MenuEntry entry) = 0;
        TTF_Font *font;
    protected:
        int selected;
        string title;
        vector<MenuEntry> entries;
        vector<Menu> menus;
        int transOnTime;
        int transOffTime;

        SDL_Surface *background;
    private:

};

#endif // MENU_H
