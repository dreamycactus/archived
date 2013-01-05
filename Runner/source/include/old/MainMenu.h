#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include "CGameEngine.h"

#define TRANS_ON        24
#define TRANS_OFF       18


class MainMenu : public Menu
{
    public:
        MainMenu();
        void Init();
        void HandleInput(CGameEngine *game);
        void SelectEntry(int entryIndex);
        void Cancel();
        void Update();
        void Draw(CGameEngine *game);
        void Cleanup();
        void AddEntry(MenuEntry entry);
    private:
};

#endif // MAINMENU_H

