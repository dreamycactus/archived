/* Include windows.h properly on Windows */
#if defined(WIN32) || defined(_WINDOWS)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/* SDL */
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#ifndef HELLO_MAGIC_MAIN
#  undef main
#endif

#include <iostream>
#include "CORE_cGame.hpp"
#include "STATE_iGameState.hpp"

#include "lesson5Blending_state.hpp"
#include "Bitmaps3D.hpp"
#include "WavingBitmap_State.hpp"
#include "Particle_State.hpp"

using namespace CORE;
using namespace std;

// Main function must have these params for SDL... kinda lame for encapsulation here..
void RegisterStates()
{
    cGame::state_factory.RegisterClass("blend", cLesson5Blending::CreateInstance);
    cGame::state_factory.RegisterClass("bitmap", Bitmaps3DState::CreateInstance);
    cGame::state_factory.RegisterClass("waving", WavingBitmap_State::CreateInstance);
    cGame::state_factory.RegisterClass("particle", Particle_State::CreateInstance);
}

int main(int argc, char* args[])
{
    bool running        = true;
    iApplication* game  = new cGame();

    RegisterStates();

    cout << "Choose one of the following programs to run, q to quit\n";
    while (running) {
        char c;
        cGame* g = dynamic_cast<cGame*>(game);
        STATE::iGameState* state = 0;

        cout << "1 Blending 3D Textures\n";
        cout << "2 3D Rotating Bitmaps\n";
        cout << "3 Waving Bitmap\n";
        cout << "4 Particle engine\n";

        cin >> c;
        switch (c) {
            case '1':
                state = cGame::state_factory.CreateObject("blend");
                break;
            case '2':
                state = cGame::state_factory.CreateObject("bitmap");
                break;
            case '3':
                state = cGame::state_factory.CreateObject("waving");
                break;
            case '4':
                state = cGame::state_factory.CreateObject("particle");
                break;
            case 'q':
                running = false;
                state = 0;
                break;
            default:
                cout << "Invalid choice\n";
                continue;
        }

        if (state!=0 && g->Initialise()) {
            g->GetStateManager().PushState(state);
            g->MainLoop();
            g->Terminate();
        }
    }


    delete game;

    return 0;
}
