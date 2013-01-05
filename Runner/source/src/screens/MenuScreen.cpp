#include "../../include/screens/MenuScreen.h"
#include "../../include/screens/GameScreen.h"


MenuScreen* MenuScreen::inst = 0;

MenuScreen* MenuScreen::instance()
{
    if (inst == 0)
        inst = new MenuScreen;
    return inst;
}

bool MenuScreen::Init()
{
    background = load_image("sprites/mainmenu.png");
    return true;
}

void MenuScreen::Cleanup()
{
    /* Free Surfaces HERE*/
    SDL_FreeSurface(background);
    delete inst;
    inst = 0;
}

void MenuScreen::Pause(){}
void MenuScreen::Resume(){}

void MenuScreen::HandleInput(CGameEngine* game)
{

    SDL_Event event = game->GetEvent();
    if( event.type == SDL_KEYDOWN )
    {
        game->ChangeState(GameScreen::instance());/*
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: ; break;
            case SDLK_LEFT: ; break;
            default: ; break;
        }*/
    }
    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: ; break;
            case SDLK_LEFT: ; break;
            default: ; break;
        }
    }/*
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if(keystates[SDLK_RIGHT])
    {

    }
    else if (keystates[SDLK_LEFT])
    {
    }*/
}

void MenuScreen::Update(CGameEngine* game)
{

}

void MenuScreen::Draw(CGameEngine* game)
{

    //Fill the screen white
    SDL_FillRect( game->GetScreen(), &game->GetScreen()->clip_rect, SDL_MapRGB( game->GetScreen()->format, 0xFF, 0x00, 0x00 ) );
    apply_surface(Vector2D(0.0, 0.0), background, game->GetScreen());


    if( SDL_Flip( game->GetScreen() ) == -1 ) { /*output to debug file */}
}
