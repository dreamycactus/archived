#include "../../include/screens/MainMenuScreen.h"
#include "../../include/screens/GameScreen.h"
#include "../../include/screens/QuitScreen.h"



MainMenuScreen MainMenuScreen::inst;

bool MainMenuScreen::Init()
{
    music1 = Mix_LoadMUS("sounds/menu_loop.mp3");
    sprite_bg = load_image("sprites/menus/main_menu_bg.png");
    sprite_bg_instr = load_image("sprites/menus/instr_bg.png");
    sprite_bg_credit = load_image("sprites/menus/credit_bg.png");
    sprite_play = load_image("sprites/menus/play.png");
    sprite_quit = load_image("sprites/menus/quit.png");
    sprite_credit = load_image("sprites/menus/credit.png");
    sprite_instr = load_image("sprites/menus/instr.png");

    state = MAIN;
    guard = false;
    return true;
}

void MainMenuScreen::Cleanup()
{
    /* Free Surfaces HERE*/
    SDL_FreeSurface(sprite_bg);
    SDL_FreeSurface(sprite_bg_instr);
    SDL_FreeSurface(sprite_bg_credit);
    SDL_FreeSurface(sprite_play);
    SDL_FreeSurface(sprite_instr);
    SDL_FreeSurface(sprite_credit);
    SDL_FreeSurface(sprite_quit);
    Mix_FreeMusic(music1);
}

void MainMenuScreen::Pause(){}
void MainMenuScreen::Resume(){}

void MainMenuScreen::HandleInput(CGameEngine* game)
{
    Uint8 *keystates = SDL_GetKeyState(NULL);
    switch(state)
    {
        case MAIN:
            if (!keystates[SDLK_LEFT] && !keystates[SDLK_ESCAPE])
                guard = true;
            if (guard && (keystates[SDLK_LEFT] || keystates[SDLK_ESCAPE]))
            {
                game->Quit();
            }
            else if (keystates[SDLK_RIGHT])
            {
                game->ChangeState(GameScreen::instance());
            }
            else if (keystates[SDLK_UP])
            {
                state = CREDIT;
            }
            else if (keystates[SDLK_DOWN])
            {
                state = INSTR;
            }

            break;
        case CREDIT:
            guard = false;
            if (keystates[SDLK_LEFT] || keystates[SDLK_ESCAPE])
            {
                state = MAIN;
            }
            else if (keystates[SDLK_RIGHT])
            {
                game->ChangeState(GameScreen::instance());
            }
            break;
        case INSTR:
            guard = false;
            if (keystates[SDLK_LEFT] || keystates[SDLK_ESCAPE])
            {
                state = MAIN;
            }
            else if (keystates[SDLK_RIGHT])
            {
                game->ChangeState(GameScreen::instance());
            }
            break;
    }

}

void MainMenuScreen::Update(CGameEngine* game)
{
    if( Mix_PlayingMusic() == 0 ) { Mix_PlayMusic( music1, -1 ); }
}

void MainMenuScreen::Draw(CGameEngine* game)
{

    //Fill the screen white
    //SDL_FillRect( game->GetScreen(), &game->GetScreen()->clip_rect, SDL_MapRGB(game->GetScreen()->format, 0xFF, 0x00, 0x00 ));

    switch(state)
    {
        case MAIN:
            apply_surface(Vector2D(0,0), sprite_bg, game->GetScreen());
            apply_surface(Vector2D(300,100), sprite_play, game->GetScreen());
            apply_surface(Vector2D(300,130), sprite_instr, game->GetScreen());
            apply_surface(Vector2D(300,160), sprite_credit, game->GetScreen());
            apply_surface(Vector2D(300,190), sprite_quit, game->GetScreen());
            break;
        case INSTR:
            apply_surface(Vector2D(0,0), sprite_bg_instr, game->GetScreen());
            break;
        case CREDIT:
            apply_surface(Vector2D(0,0), sprite_bg_credit, game->GetScreen());
            break;
    }


    if( SDL_Flip( game->GetScreen() ) == -1 ) { /*output to debug file */}
}
