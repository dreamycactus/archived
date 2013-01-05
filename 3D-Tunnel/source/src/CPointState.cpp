#include "CPointState.h"

#include <string>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "gl/glext.h"
#include <boost/shared_ptr.hpp>

#include "mytypes.h"
#include "helper.h"
#include "graphics/shapes.h"
#include "Input.h"
#include "CObjMeshParser.h"
#include "tokens/CMesh.h"
#include "tokens/CMaterial.h"
#include "math/dcRandom.h"
#include <iostream>

using std::cout;
using std::endl;
using boost::shared_ptr;

CPointState::CPointState(int w, int h) :
WIDTH(w),
HEIGHT(h)
{
}
CPointState::~CPointState()
{
}
void CPointState::cleanup()
{
}
void initGL()
{
//    glEnable(GL_CULL_FACE);
    glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
	glEnable( GL_TEXTURE_2D );									// Enable Textures

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing

	GLfloat global_ambient[4]={0.7f, 0.7f,  0.7f, 1.0f};		// Set Ambient Lighting To Fairly Dark Light (No Color)
//	GLfloat global_ambient[4]={0.1f, 0.1f,  0.1f, 1.0f};		// Set Ambient Lighting To Fairly Dark Light (No Color)
	GLfloat light0pos[4]=     {0.0f, 5.0f, 10.0f, 1.0f};		// Set The Light Position
	GLfloat light0ambient[4]= {0.2f, 0.2f,  0.2f, 1.0f};		// More Ambient Light
//	GLfloat light0diffuse[4]= {0.3f, 0.3f,  0.3f, 1.0f};		// Set The Diffuse Light A Bit Brighter
	GLfloat light0diffuse[4]= {1.0f, 1.0f,  1.0f, 1.0f};		// Set The Diffuse Light A Bit Brighter
//	GLfloat light0diffuse[4]= {0.0f, 0.0f,  0.0f, 0.0f};		// Set The Diffuse Light A Bit Brighter
//	GLfloat light0specular[4]={0.0f, 0.0f,  0.0f, 0.0f};		// Fairly Bright Specular Lighting
	GLfloat light0specular[4]={6.0f, 6.0f,  6.0f, 1.0f};		// Fairly Bright Specular Lighting

	GLfloat light1ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light1diffuse[4]=  {1.0f, 1.0f,  1.0f, 1.0f};
	GLfloat light1specular[4]= {1.0f, 1.0f,  1.0f, 1.0f};
	GLfloat light1direction[3] = { 0.0f, -1.0f, 0.0f };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1ambient);			// Set The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1diffuse);			// Set The Diffuse Light
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1specular);	    // Set Up Specular Lighting
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0f);

	GLfloat lmodel_ambient[]= {0.2f,0.2f,0.2f,1.0f};			// And More Ambient Light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);		// Set The Ambient Light Model

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);		// Set The Global Ambient Light Model
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);				// Set The Lights Position
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0ambient);			// Set The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0diffuse);			// Set The Diffuse Light
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0specular);	    // Set Up Specular Lighting

	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 10.f);

	glEnable(GL_LIGHTING);										// Enable Lighting
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);									// Select Smooth Shading

	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(1.0f, 1.0f, 0.9f, 0.5f);						// Set The Clear Color To Black
    dcVBO::init();
}

void CPointState::init()
{

    initGL();
    SDL_ShowCursor(SDL_DISABLE);

    paused_ = false;
    lighting_ = true;

    const Vec3f   CAMERA_ACCELERATION(8.0f, 8.0f, 8.0f);
    const float   CAMERA_FOVX = 90.0f;
    const Vec3f   CAMERA_POS(0.0f, 0.0f, 10.0f);
    const float   CAMERA_SPEED_ROTATION = 0.2f;
    const float   CAMERA_SPEED_FLIGHT_YAW = 100.0f;
    const Vec3f   CAMERA_VELOCITY(20.0f, 20.0f, 20.0f);
    const float   CAMERA_ZFAR = 1000.0f;
    const float   CAMERA_ZNEAR = 0.1f;

    cam_.perspective(CAMERA_FOVX,
        static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
        CAMERA_ZNEAR, CAMERA_ZFAR);
    cam_.setBehavior(CCamera::CAMERA_BEHAVIOR_FIRST_PERSON);
    cam_.setPos(CAMERA_POS);
    cam_.setAccel(CAMERA_ACCELERATION);
    cam_.setVel(CAMERA_VELOCITY);

    ang_x_ = ang_y_ = 0.0f;

    material_.ka = { 0.19125f, 0.0735f, 0.0225f };
    material_.ks = { 0.256777f, 0.137622f, 0.086014f };
    material_.kd = { 0.7038f, 0.27048f, 0.0828f };
    material_.ns = 0.1f;


    tun.init(8 , 11, 10.0f, 10.0f);
    level_.init();
}

void CPointState::GetMovementDirection(Vec3f& direction)
{
    Vec3f velocity = cam_.getCurrentVel();
    direction.set(0.0f, 0.0f, 0.0f);
    float depth = level_.getShipDepth();
    const static float FOLLOW_DISTANCE = 20.0f;
    float delta = depth+FOLLOW_DISTANCE - cam_.getPos().z;

    if (delta<0)
    {
        cam_.move(0.0f,0.0f,-delta);
    }

    if (Input::key_down(HAR_w))
    {
        direction.z += 1.0f;
        if (Input::key_just_pressed(HAR_w))
        {
            cam_.setCurrentVel(velocity.x, velocity.y, 0.0f);
        }
    }
    if (Input::key_down(HAR_s))
    {
        direction.z -= 1.0f;
        if (Input::key_just_pressed(HAR_s))
        {
            cam_.setCurrentVel(velocity.x, velocity.y, 0.0f);
        }
    }
    if (Input::key_down(HAR_d))
    {
        direction.x += 1.0f;
        if (Input::key_just_pressed(HAR_d))
        {
            cam_.setCurrentVel(0.0f, velocity.y, velocity.z);
        }
    }
    if (Input::key_down(HAR_a))
    {
        direction.x -= 1.0f;
        if (Input::key_just_pressed(HAR_a))
        {
            cam_.setCurrentVel(0.0f, velocity.y, velocity.z);
        }
    }
    if (Input::key_down(HAR_q))
    {
        direction.y -= 1.0f;
        if (Input::key_just_pressed(HAR_q))
        {
            cam_.setCurrentVel(velocity.x, 0.0f, velocity.z);
        }
    }
    if (Input::key_down(HAR_e))
    {
        direction.y += 1.0f;
        if (Input::key_just_pressed(HAR_e))
        {
            cam_.setCurrentVel(velocity.x, 0.0f, velocity.z);
        }
    }
}

void CPointState::handleInput()
{
    static bool gravity = true;
    static bool wind = false;
    static int friction = 0;

    if (Input::key_just_pressed(HAR_l))
    {
        lighting_ = !lighting_;
    }
    if (Input::key_just_pressed (HAR_p))
    {
        paused_ = !paused_;
    }

}

void CPointState::tick(float delta)
{
    handleInput();

    if (paused_) { return; }


    level_.tick(delta);
    if (!level_.ship_.active_)
    {
        init();
    }
    updateCamera(delta/1000.0f);

}
#define BUFFER_OFFSET(i) ((char*)NULL + (i))
void CPointState::render(float delta)
{
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&cam_.getProjectionMatrix()[0][0]);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(&cam_.getViewMatrix()[0][0]);
//
//    GLfloat light0pos[4]=     {0, 0, cam_.getPos().z-20.0f , 1.0f};		// Set The Light Position
//    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);				// Set The Lights Position

//    glBegin(GL_QUADS);
//        glColor3f(1,0,0);
//        glVertex3f(-1.0f,-1.0f,-2.f);
//        glVertex3f(1.0f,-1.0f,-2.f);
//        glVertex3f(1.0f,1.0f,-2.f);
//        glVertex3f(-1.0f,1.0f,-2.f);
//    glEnd();
//    tun.render();
    level_.render(delta);

}


float angle = 0.0f;


void CPointState::updateCamera(float delta)
{
    float heading   = 0.0f;
    float pitch     = 0.0f;
    float roll      = 0.0f;
    int x, y;
    Vec3f direction(0.0f, 0.0f, 0.0f);

    GetMovementDirection(direction);
    Input::get_mouse_pos(x, y);

    pitch = (HEIGHT/2.0f-y) * 0.02f;
    heading = (WIDTH/2.0f-x) * 0.02f;

//    cout << cam_.getPos().x << ", " << cam_.getPos().y << "," << cam_.getPos().z << endl;

//    cam_.rotate(heading, pitch, 0.0f);

    Vec3f pos = cam_.getPos();
    cam_.setPos(pos);
    cam_.updatePos(direction, delta);

    SDL_WarpMouse(WIDTH/2.0f, HEIGHT/2.0f);
}

bool CPointState::withinBounds(int x, int y)
{
    return (x>=0 && x<WIDTH && y>=0 && y<HEIGHT);
}
