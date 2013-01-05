#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include "Lesson5Blending_state.hpp"
#include "memory_macros.h"
#include "CORE_cGame.hpp"
#include "GFX_cImage.hpp"
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_GfxHelper.hpp"

    #include <iostream>
    using namespace std;

using namespace GFX;
using namespace GFX::G2D;

namespace
{
    bool    light;                      // Lighting ON/OFF
    bool    blend;                      // Blending OFF/ON? ( NEW )
    GLfloat xrot;                       // X Rotation
    GLfloat yrot;                       // Y Rotation
    GLfloat xspeed;                     // X Rotation Speed
    GLfloat yspeed;                     // Y Rotation Speed

    GLfloat z=-5.0f;                    // Depth Into The Screen

    GLfloat LightAmbient[]=  { 0.5f, 0.5f, 0.5f, 1.0f };    // Ambient Light Values
    GLfloat LightDiffuse[]=  { 1.0f, 1.0f, 1.0f, 1.0f };    // Diffuse Light Values
    GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };    // Light Position

    GLuint  filter;                     // Which Filter To Use
    cTexture* pTexture;                 // Storage for 3 textures
}

cLesson5Blending::cLesson5Blending() {}
cLesson5Blending::~cLesson5Blending() {}

STATE::iGameState* cLesson5Blending::CreateInstance()
{
    return new cLesson5Blending;
}
STATE::iGameState* cLesson5Blending::Clone()
{
    return new cLesson5Blending;
}

bool cLesson5Blending::OnEnter()
{
    cout << "Entering State\n";
    test = true;

    blend = true;

    pTexture = new cTexture("data/Glass.png");
    pTexture->RegisterGL();

    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One

	glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness.  50% Alpha
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();

    return true;
}
bool cLesson5Blending::OnExit()
{
    cout << "Leaving state\n";
    DELETESINGLE(pTexture)
}
void cLesson5Blending::Pause() {}
void cLesson5Blending::Resume() {}


void cLesson5Blending::Update(CORE::cGame* game, float delta)
{
    HandleInput(game);
}

void cLesson5Blending::Render(CORE::cGame* game, float percent_tick)
{
    static G2D::cSpriteBatch batch = G2D::cSpriteBatch();

    if(blend) {
        glEnable(GL_BLEND);     // Turn Blending On
        glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    }
    else{
        glDisable(GL_BLEND);        // Turn Blending Off
        glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
    }

    glBindTexture(GL_TEXTURE_2D, pTexture->GetID());
//    glLoadIdentity();


	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glRotatef(1.0f, 0.1f, 0.1f, 0.0f);
}

void cLesson5Blending::HandleInput(CORE::cGame* game)
{
    CORE::Input& input = game->GetInput();

    if (input.OnKeyUp(HAR_ESCAPE)) {
        game->EndGame();
    }
    if (input.OnKeyDown(HAR_a)) {
    	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);					// Set The Blending Function For Translucency}
    }
    if (input.OnKeyDown(HAR_b)) {
    	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency}
    }
}
