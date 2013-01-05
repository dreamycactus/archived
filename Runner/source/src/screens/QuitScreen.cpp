#include "../../include/screens/QuitScreen.h"


QuitScreen QuitScreen::inst;

QuitScreen::QuitScreen()
{
    //ctor
}

QuitScreen::~QuitScreen()
{

}
bool QuitScreen::Init()
{
    return true;
}

void QuitScreen::Cleanup()
{

}

void QuitScreen::Pause(){}
void QuitScreen::Resume(){}

void QuitScreen::HandleInput(CGameEngine* game)
{
}

void QuitScreen::Update(CGameEngine* game)
{

}

void QuitScreen::Draw(CGameEngine* game)
{
    game->Quit();
}
