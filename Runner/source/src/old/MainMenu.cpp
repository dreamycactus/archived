#include "../include/MainMenu.h"


MainMenu::MainMenu()
{
}
void MainMenu::Init()
{
    selected = 0;
    title = "Main Menu";
    transOnTime = TRANS_ON;
    transOffTime = TRANS_OFF;
    font = TTF_OpenFont( "lazy.ttf", 28 );
    background = load_image("sprites/menus/main_menu_bg.png");
}
void MainMenu::HandleInput(CGameEngine *game)
{
    SDL_Event event = game->GetEvent();
    entries[selected].SetSelect(false);
    bool tempEs = false;
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_DOWN:
                if (selected != entries.size() - 1)
                    ++selected;
                break;
            case SDLK_UP:
                if (selected != 0)
                    --selected;
                break;
            case SDLK_RETURN:
                entries[selected].Action(game);
                return;
            case SDLK_ESCAPE:
                tempEs = true;
            default: break;
        }
    }
    else if(event.type == SDL_KEYUP)
        if(event.key.keysym.sym == SDLK_ESCAPE && tempEs == true)
            game->Quit();


    entries[selected].SetSelect(true);



}

void MainMenu::Update()
{
    for (unsigned int i = 0; i < entries.size(); ++i)
    {
        entries[i].Update();
    }
}

void MainMenu::Draw(CGameEngine *game)
{
    apply_surface(Vector2D(0, 0), background, game->GetScreen());
    for (unsigned int i = 0; i < entries.size(); ++i)
    {
        entries[i].Draw(game, font);
    }

}

void MainMenu::SelectEntry(int entryIndex)
{
    selected = entryIndex;
}

void MainMenu::Cancel()
{

}


void MainMenu::Cleanup()
{
    SDL_FreeSurface(background);
    entries.clear();
}
void MainMenu::AddEntry(MenuEntry entry)
{
    entries.push_back(entry);
}
