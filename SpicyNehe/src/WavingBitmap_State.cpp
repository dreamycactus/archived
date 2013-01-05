#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include "WavingBitmap_State.hpp"
#include "CORE_cGame.hpp"
#include "GFX_cImage.hpp"
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_GfxHelper.hpp"

    #include <iostream>
    #include <GL/glu.h>
    using namespace std;

using namespace GFX;
using namespace GFX::G2D;

namespace
{
    float points[45][45][3];    // The Array For The Points On The Grid Of Our "Wave"
    int wiggle_count = 0;		// Counter Used To Control How Fast Flag Waves

    GLfloat	xrot;				// X Rotation ( NEW )
    GLfloat	yrot;				// Y Rotation ( NEW )
    GLfloat	zrot;				// Z Rotation ( NEW )
    GLfloat hold;				// Temporarily Holds A Floating Point Value
    cTexture* p_tex;
}

WavingBitmap_State::WavingBitmap_State() {}
WavingBitmap_State::~WavingBitmap_State() {}

STATE::iGameState* WavingBitmap_State::CreateInstance()
{
    return new WavingBitmap_State;
}
STATE::iGameState* WavingBitmap_State::Clone()
{
    return new WavingBitmap_State;
}

//cTexture* p_tex2;
bool WavingBitmap_State::OnEnter()
{
    cout << "Entering State\n";
    p_tex = new cTexture("data/Tim.png");
    p_tex->RegisterGL();

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)640/(GLfloat)480,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();

    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glPolygonMode( GL_BACK, GL_FILL );					// Back Face Is Solid
	glPolygonMode( GL_FRONT, GL_FILL );					// Front Face Is Made Of Lines

	for(int x=0; x<45; x++)
	{
		for(int y=0; y<45; y++)
		{
			points[x][y][0]=float((x/5.0f)-4.5f);
			points[x][y][1]=float((y/5.0f)-4.5f);
			points[x][y][2]=float(sin((((x/5.0f)*40.0f)/360.0f)*PI*2.0f));
		}
	}

    return true;
}
bool WavingBitmap_State::OnExit()
{
    cout << "Leaving state\n";
}
void WavingBitmap_State::Pause() {}
void WavingBitmap_State::Resume() {}


void WavingBitmap_State::Update(CORE::cGame* game, float delta)
{
    HandleInput(game);
    int x, y;
    if( wiggle_count == 2 )
	{
		for( y = 0; y < 45; y++ )
		{
			hold = points[0][y][2];
			for( x = 0; x < 44; x++)
			{
				points[x][y][2] = points[x+1][y][2];
			}
			points[44][y][2] = hold;
		}
		wiggle_count = 0;
	}

	wiggle_count++;

//	xrot+=0.3f;
	yrot+=0.2f;
//	zrot+=0.4f;
}

void WavingBitmap_State::Render(CORE::cGame* game, float percent_tick)
{
    int x, y;
	float float_x, float_y, float_xb, float_yb;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View

	glTranslatef(0.0f,0.0f,-12.0f);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D, p_tex->GetID());

	glBegin(GL_QUADS);
	for( x = 0; x < 44; x++ )
	{
		for( y = 0; y < 44; y++ )
		{
			float_x = float(x)/44.0f;
			float_y = float(y)/44.0f;
			float_xb = float(x+1)/44.0f;
			float_yb = float(y+1)/44.0f;

			glTexCoord2f( float_x, float_y);
			glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );

			glTexCoord2f( float_x, float_yb );
			glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );

			glTexCoord2f( float_xb, float_yb );
			glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );

			glTexCoord2f( float_xb, float_y );
			glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
		}
	}
	glEnd();
}

void WavingBitmap_State::HandleInput(CORE::cGame* game)
{
    CORE::Input& input = game->GetInput();

    if (input.OnKeyUp(HAR_ESCAPE)) game->EndGame();
    if (input.OnKeyDown(HAR_a)) { test = !test; }
    if (input.OnKeyDown(HAR_b)) { game->GetStateManager().ReplaceState(game->state_factory.CreateObject("game")); }
}
