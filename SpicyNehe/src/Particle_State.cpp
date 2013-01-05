#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include "Particle_State.hpp"
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
    #define	MAX_PARTICLES	1000		// Number Of Particles To Create

    bool	rainbow=true;
    float	slowdown=2.0f;				// Slow Down Particles
    float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
    float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
    float	zoom=-40.0f;				// Used To Zoom Out

    GLuint	loop;						// Misc Loop Variable
    GLuint	col;						// Current Color Selection
    GLuint	delay;						// Rainbow Effect Delay

    struct particles						// Create A Structure For Particle
    {
        bool	active;					// Active (Yes/No)
        float	life;					// Particle Life
        float	fade;					// Fade Speed
        float	r;						// Red Value
        float	g;						// Green Value
        float	b;						// Blue Value
        float	x;						// X Position
        float	y;						// Y Position
        float	z;						// Z Position
        float	xi;						// X Direction
        float	yi;						// Y Direction
        float	zi;						// Z Direction
        float	xg;						// X Gravity
        float	yg;						// Y Gravity
        float	zg;						// Z Gravity
    };

    particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)
    static GLfloat colors[12][3]=		// Rainbow Of Colors
    {
        {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
        {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
        {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
    };
}

Particle_State::Particle_State() {}
Particle_State::~Particle_State() {}

STATE::iGameState* Particle_State::CreateInstance()
{
    return new Particle_State;
}
STATE::iGameState* Particle_State::Clone()
{
    return new Particle_State;
}

cTexture* p_tex;
//cTexture* p_tex2;
bool Particle_State::OnEnter()
{
    cout << "Entering State\n";
    p_tex = new cTexture("data/Particle.png");
    p_tex->RegisterGL();

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)640.0f/(GLfloat)480.0f,0.1f,200.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D,p_tex->GetID());			// Select Our Texture

	for (loop=0;loop<MAX_PARTICLES;loop++)				// Initials All The Textures
	{
		particle[loop].active=true;								// Make All The Particles Active
		particle[loop].life=1.0f;								// Give All The Particles Full Life
		particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];	// Select Red Rainbow Color
		particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];	// Select Red Rainbow Color
		particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];	// Select Red Rainbow Color
		particle[loop].xi=float((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
		particle[loop].xg=0.0f;									// Set Horizontal Pull To Zero
		particle[loop].yg=-0.8f;								// Set Vertical Pull Downward
		particle[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
	}

    test = false;

    return true;
}
bool Particle_State::OnExit()
{
    cout << "Leaving state\n";
}
void Particle_State::Pause() {}
void Particle_State::Resume() {}




void Particle_State::Update(CORE::cGame* game, float delta)
{
    HandleInput(game);
    if (rainbow && delay > 25) {
        delay=0;						// Reset The Rainbow Color Cycling Delay
        col++;							// Change The Particle Color
        if (col>11)	col=0;				// If Color Is To High Reset
    }
    delay++;
}

void Particle_State::Render(CORE::cGame* game, float percent_tick)
{
    glLoadIdentity();										// Reset The ModelView Matrix

	for (loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
	{
		if (particle[loop].active)							// If The Particle Is Active
		{
			float x=particle[loop].x;						// Grab Our Particle X Position
			float y=particle[loop].y;						// Grab Our Particle Y Position
			float z=particle[loop].z+zoom;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle[loop].x+=particle[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particle[loop].z+=particle[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
			particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
			particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
			particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

			if (particle[loop].life<0.0f)					// If Particle Is Burned Out
			{
				particle[loop].life=1.0f;					// Give It New Life
				particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				particle[loop].x=0.0f;						// Center On X Axis
				particle[loop].y=0.0f;						// Center On Y Axis
				particle[loop].z=0.0f;						// Center On Z Axis
				particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
				particle[loop].r=colors[col][0];			// Select Red From Color Table
				particle[loop].g=colors[col][1];			// Select Green From Color Table
				particle[loop].b=colors[col][2];			// Select Blue From Color Table
			}
		}
	}
}

void Particle_State::HandleInput(CORE::cGame* game)
{
    CORE::Input& input = game->GetInput();

    if (input.OnKeyUp(HAR_ESCAPE)) game->EndGame();

    if (input.GetKeyState(HAR_w) && (particle[loop].yg<1.5f)) for (loop=0; loop<MAX_PARTICLES; ++loop) particle[loop].yg+=0.01f;

    // If Number Pad 2 And Y Gravity Is Greater Than -1.5 Increase Pull Downwards
    if (input.GetKeyState(HAR_s) && (particle[loop].yg>-1.5f)) for (loop=0; loop<MAX_PARTICLES; ++loop) particle[loop].yg-=0.01f;

    // If Number Pad 6 And X Gravity Is Less Than 1.5 Increase Pull Right
    if (input.GetKeyState(HAR_d) && (particle[loop].xg<1.5f)) for (loop=0; loop<MAX_PARTICLES; ++loop) particle[loop].xg+=0.01f;

    // If Number Pad 4 And X Gravity Is Greater Than -1.5 Increase Pull Left
    if (input.GetKeyState(HAR_a) && (particle[loop].xg>-1.5f)) for (loop=0; loop<MAX_PARTICLES; ++loop)  particle[loop].xg-=0.01f;

    if (input.OnKeyUp(HAR_r)) rainbow = !rainbow;

    if (input.OnKeyUp(HAR_SPACE))										// Tab Key Causes A Burst
    {
        for (loop=0; loop<MAX_PARTICLES; ++loop)  {
            particle[loop].x=0.0f;								// Center On X Axis
            particle[loop].y=0.0f;								// Center On Y Axis
            particle[loop].z=0.0f;								// Center On Z Axis
            particle[loop].xi=float((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
            particle[loop].yi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
            particle[loop].zi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Z Axis
        }
    }

}
