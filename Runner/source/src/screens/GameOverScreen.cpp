#include "../../include/screens/GameOverScreen.h"


GameOverScreen GameOverScreen::inst;

GameOverScreen::GameOverScreen()
{

}

GameOverScreen::~GameOverScreen()
{

}
bool GameOverScreen::Init()
{

    sprite1 = load_image("sprites/menus/gameover.png");
    sprite2 = load_image("sprites/menus/gameOver_select.png");
    soundSlash.load_sound("sounds/gameover.wav");
    notPlayed = true;
    quit = false;
    execute = false;
    alpha = 255;
    return true;
}

void GameOverScreen::Cleanup()
{
    SDL_FreeSurface(sprite1);
    SDL_FreeSurface(sprite2);
    soundSlash.Cleanup();
}

void GameOverScreen::Pause(){}
void GameOverScreen::Resume(){}

void GameOverScreen::HandleInput(CGameEngine* game)
{
    SDL_Event event = game->GetEvent();

    Uint8 *keystates = SDL_GetKeyState(NULL);
    if (keystates[SDLK_LEFT] || keystates[SDLK_ESCAPE])
    {
        quit = true;
        execute = true;
    }
    else if (keystates[SDLK_RIGHT])
    {
        quit = false;
        execute = true;
    }

}

void GameOverScreen::Update(CGameEngine* game)
{
    if (notPlayed)
    {
        soundSlash.Play();
        notPlayed = false;
    }
            if (execute)
    {
        SDL_SetAlpha(sprite1, SDL_SRCALPHA, alpha);
        SDL_SetAlpha(sprite2, SDL_SRCALPHA, alpha);
        alpha -= 10;
        if (alpha <= 0)
        {
            if (quit)
                game->ChangeState(MainMenuScreen::instance());
            else
                game->ChangeState(GameScreen::instance());
        }

    }
}

void GameOverScreen::Draw(CGameEngine* game)
{
    SDL_FillRect( game->GetScreen(), &game->GetScreen()->clip_rect, SDL_MapRGB( game->GetScreen()->format, 0xFF, 0xFF, 0xFF ) );
    if (quit)
        apply_surface(Vector2D(0, 0), sprite1, game->GetScreen());
    else
        apply_surface(Vector2D(0, 0), sprite2, game->GetScreen());
}
