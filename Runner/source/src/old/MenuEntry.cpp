#include "../include/MenuEntry.h"
#include "../include/screens/GameScreen.h"

using namespace std;

MenuEntry::MenuEntry(string text, CGameState *dest, Vector2D pos, SDL_Color color, TTF_Font *font)
{
    desti = dest;
    this->text = text;
    this->pos = pos;
    this->color = color;
    this->font = font;
    alpha = 255;
    select = false;

}


void MenuEntry::Update()
{
    if (select)
        color = SDL_Color{0, 255, 255};
    else color = SDL_Color{255, 255, 255};
}

void MenuEntry::Draw(CGameEngine *game, TTF_Font *font)
{
    SDL_Surface *message = TTF_RenderText_Solid( font, text.c_str(), color );
    apply_surface(pos, message, game->GetScreen());
    SDL_FreeSurface(message);

}

void MenuEntry::Action(CGameEngine *game)
{
    game->ChangeState(desti);
}

void MenuEntry::SetSelect(bool s)
{
    select = s;
}
