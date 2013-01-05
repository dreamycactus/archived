#include "../include/CGameEngine.h"
#include "../include/CGameState.h"

CGameEngine::CGameEngine()
{
    m_running = true;
}
bool CGameEngine::Init(int screen_w, int screen_h, int screen_bpp)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) { return false; }
    screen = SDL_SetVideoMode(screen_w, screen_h, screen_bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);

    if (screen == NULL) { return false; }
    SDL_WM_SetCaption( "Animation Test", NULL );

    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->screen_bpp = screen_bpp;

    game_timer.start();
    frames = 0;

    return true;
}

void CGameEngine::Cleanup()
{
    while (!states.empty())
    {
		states.back()->Cleanup();
		states.pop_back();
	}
    Mix_CloseAudio();
    SDL_Quit();
}


void CGameEngine::ChangeState(CGameState *state)
{
    if(!states.empty())
    {
        states.back()->Cleanup();
        states.pop_back();
    }
    states.push_back(state);
    states.back()->Init();
}

void CGameEngine::HandleInput()
{
    states.back()->HandleInput(this);
}
void CGameEngine::Update()
{
    states.back()->Update(this);
}

void CGameEngine::Draw()
{
    states.back()->Draw(this);
}

void CGameEngine::PushState(CGameState *state)
{
    states.push_back(state);
}

void CGameEngine::PopState()
{
    if (!states.empty())
    {
        states.back()->Cleanup();
        states.pop_back();
        states.back()->Resume();
    }
}

void CGameEngine::Quit()
{
    m_running = false;

}

Uint32 CGameEngine::GetTicks()
{
    return game_timer.get_ticks();
}
SDL_Surface* CGameEngine::GetScreen()
{
    return screen;
}

SDL_Event CGameEngine::GetEvent()
{
    return event;
}

void CGameEngine::SetEvent(SDL_Event event)
{
    this->event = event;
}

int CGameEngine::GetWidth()
{
    return screen_w;
}
