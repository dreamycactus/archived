#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include "Bitmaps3D.hpp"
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
    bool	twinkle;			// Twinkling Stars
    bool	tp;					// 'T' Key Pressed?

    const int num=50;				// Number Of Stars To Draw

    struct Stars			// Create A Structure For Star
    {
        int r, g, b;			// Stars Color
        GLfloat dist,			// Stars Distance From Center
                angle;			// Stars Current Angle
    };
    Stars star[num];			// Need To Keep Track Of 'num' Stars

    GLfloat	zoom=-15.0f;		// Distance Away From Stars
    GLfloat tilt=90.0f;			// Tilt The View
    GLfloat	spin;				// Spin Stars

    cTexture* p_tex;
}


Bitmaps3DState::Bitmaps3DState() {}
Bitmaps3DState::~Bitmaps3DState() {}

STATE::iGameState* Bitmaps3DState::CreateInstance()
{
    return new Bitmaps3DState;
}
STATE::iGameState* Bitmaps3DState::Clone()
{
    return new Bitmaps3DState;
}


//cTexture* p_tex2;
bool Bitmaps3DState::OnEnter()
{
    cout << "Entering State Bitmaps3D\n";

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
    gluPerspective(45.0f,(GLfloat)800/(GLfloat)720,0.1f,100.0f);

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
	glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();								// Reset The Modelview Matrix

    p_tex = new cTexture("data/Star.png");
    p_tex->RegisterGL();

    test = false;
    twinkle = true;

    unsigned int loop;
    for (loop=0; loop<num; loop++) {
		star[loop].angle=0.0f;
		star[loop].dist=(float(loop)/num)*5.0f;
		star[loop].r=rand()%256;
		star[loop].g=rand()%256;
		star[loop].b=rand()%256;
	}

    return true;
}
bool Bitmaps3DState::OnExit()
{
    cout << "Leaving state Bitmaps3D \n";
}
void Bitmaps3DState::Pause() {}
void Bitmaps3DState::Resume() {}




void Bitmaps3DState::Update(CORE::cGame* game, float delta)
{
    HandleInput(game);
}

void Bitmaps3DState::Render(CORE::cGame* game, float percent_tick)
{
    static G2D::cSpriteBatch batch = G2D::cSpriteBatch();

    static cTextureRegion reg = cTextureRegion(*p_tex);
//    static cTextureRegion reg2 = cTextureRegion(*p_tex2);

    glBindTexture(GL_TEXTURE_2D, p_tex->GetID());

    glEnable(GL_BLEND);     // Turn Blending On
    glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off

    unsigned int loop;
    for (loop=0; loop<num; loop++)						// Loop Through All The Stars
	{
		glLoadIdentity();								// Reset The View Before We Draw Each Star
		glTranslatef(0.0f,0.0f,zoom);					// Zoom Into The Screen (Using The Value In 'zoom')
		glRotatef(tilt,1.0f,0.0f,0.0f);					// Tilt The View (Using The Value In 'tilt')
		glRotatef(star[loop].angle,0.0f,1.0f,0.0f);		// Rotate To The Current Stars Angle
		glTranslatef(star[loop].dist,0.0f,0.0f);		// Move Forward On The X Plane
		glRotatef(-star[loop].angle,0.0f,1.0f,0.0f);	// Cancel The Current Stars Angle
		glRotatef(-tilt,1.0f,0.0f,0.0f);				// Cancel The Screen Tilt

		if (twinkle)
		{
			glColor4ub(star[(num-loop)-1].r,star[(num-loop)-1].g,star[(num-loop)-1].b,255);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		}

		glRotatef(spin,0.0f,0.0f,1.0f);
		glColor4ub(star[loop].r,star[loop].g,star[loop].b,255);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();

		spin+=0.01f;
		star[loop].angle+=float(loop)/num;
		star[loop].dist-=0.01f;
		if (star[loop].dist<0.0f)
		{
			star[loop].dist+=5.0f;
			star[loop].r=rand()%256;
			star[loop].g=rand()%256;
			star[loop].b=rand()%256;
		}
	}
}

void Bitmaps3DState::HandleInput(CORE::cGame* game)
{
    CORE::Input& input = game->GetInput();

    if (input.OnKeyUp(HAR_ESCAPE)) {
        game->EndGame();
    }
    if (input.OnKeyDown(HAR_a)) { twinkle = !twinkle; }
    if (input.GetKeyState(HAR_LEFT)) { tilt+=0.5f; }
    if (input.GetKeyState(HAR_RIGHT)) { tilt-=0.5f; }

}
