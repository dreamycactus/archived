////////////////////////////////////////////////////////////////////////////////
/**
 * \file    main.cpp
 * \author  Hua Fei Yu 0951402
 * \date    October 8, 2011
 * \brief   Assignment 1
 */
////////////////////////////////////////////////////////////////////////////////
#include "SDL/SDL.h"
#include "SDL/SDL_main.h"
#include "SDL/SDL_opengl.h"
#include "gl/glu.h"

#include "Input.h"
#include "helper.h"
#include "CTimer.h"

#include "IGameState.h"
#include "CPointState.h"


#include <iostream>

//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;

SDL_Event event;

bool init_GL()
{
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //glShadeModel(GL_SMOOTH);
	//glClearDepth(1.0);
	glEnable( GL_DEPTH_TEST );
	//glDepthFunc( GL_LEQUAL );
	//glDepthMask( GL_TRUE );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(59, (double)(SCREEN_WIDTH)/(double)SCREEN_HEIGHT, 1, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(glGetError() != GL_NO_ERROR) { return false; }

    return true;
}

bool init()
{

    //Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_VIDEO) < 0)   { return false; }

    //Create Window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL|SDL_HWSURFACE|SDL_DOUBLEBUF) == NULL) { return false; }

    //Initialize OpenGL
    if (init_GL() == false) { return false; }

    //Set caption
    SDL_WM_SetCaption("OpenGL Test", NULL);

    SDL_WM_GrabInput(SDL_GRAB_ON);

    return true;
}

void clean_up()
{
    SDL_Quit();
}

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    cout << "here";
    bool running        = true;
    CTimer fps;
    IGameState* state   = new CPointState(SCREEN_WIDTH, SCREEN_HEIGHT);
    float delta         = 0.f;
    float factor        = 1.f;

    if (init() == false) { return 1; }
    state->init();
    Input::init();
    fps.start();


	while (running)
	{

        while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) { running = false; }
		}
		// Some input stuff
		if (Input::key_down(HAR_ESCAPE))        { running = false; }
		if (Input::key_just_pressed(HAR_PLUS))  { factor -= 0.25f; }
		if (Input::key_just_pressed(HAR_MINUS)) { factor += 0.25f; }

		factor = clamp(factor, 0.5f, 5.f);
        delta = fps.get_delta()/factor;

        Input::tick();
		state->tick(delta);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		state->render(delta);

        //Update screen
	    SDL_GL_SwapBuffers();

	    Uint8* keystate = SDL_GetKeyboardState(0);
//	    for (int i=0; i<200; ++i) if (keystate[i]) cout << i << endl;

	}


    delete state;
	state = 0;

	clean_up();

    cout << "exit" << endl;
	return 0;
}
