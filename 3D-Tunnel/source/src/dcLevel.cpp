#include "dcLevel.h"
#include "input.h"
#include "CParticleManager.h"

GLuint blur_texture;

dcLevel::dcLevel() :
ship_(dcShip()),
endless_(dcTunnelStrip())
{
}

dcLevel::~dcLevel()
{
    //dtor
}

void dcLevel::init()
{
    ship_.init();
    ship_.particles = &particles_;
    endless_.init();
//    tunnel_.init(8 , 11, 10.0f, 10.0f);
    dcRailPos::radius = 6.7f;
    spawner_.particles = &particles_;
    spawner_.init();
    endless_.spawner = &spawner_;
    spawner_.spawnMany(endless_.getCurrentDepth(), endless_.getCurrentDepth()-endless_.getCurrentTunnelLength(), endless_.getRadius()-2.0f, 10);

    blur_texture = createEmptyTexture(128, 128);
    particles_.init();
}

void dcLevel::handleInput(float delta)
{
    if (Input::key_down(HAR_LEFT))
    {
        ship_.thrust(LEFT, delta);
    }
    if (Input::key_down(HAR_RIGHT))
    {
        ship_.thrust(RIGHT, delta);
    }
}

void dcLevel::tick(float delta)
{
    handleInput(delta);

    ship_.tick(delta/10.0f);
    spawner_.tick(delta, ship_);
    endless_.tick(delta, ship_.getPos().depth+20.0f);
    particles_.tick(delta);
}
int WIDTH = 1024, HEIGHT = 768;
void dcLevel::renderToTexture()
{
    glViewport(0, 0, 128, 128);

    ship_.getMesh()->render();

    glBindTexture(GL_TEXTURE_2D, blur_texture);

    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, WIDTH, HEIGHT);
}


void ViewOrtho()                            // Set Up An Ortho View
{
    glMatrixMode(GL_PROJECTION);                    // Select Projection
    glPushMatrix();                         // Push The Matrix
    glLoadIdentity();                       // Reset The Matrix
    glOrtho( 0, WIDTH , HEIGHT , 0, -1, 1 );             // Select Ortho Mode (640x480)
    glMatrixMode(GL_MODELVIEW);                 // Select Modelview Matrix
    glPushMatrix();                         // Push The Matrix
    glLoadIdentity();                       // Reset The Matrix
}

void ViewPerspective()                          // Set Up A Perspective View
{
    glMatrixMode( GL_PROJECTION );                  // Select Projection
    glPopMatrix();                          // Pop The Matrix
    glMatrixMode( GL_MODELVIEW );                   // Select Modelview
    glPopMatrix();                          // Pop The Matrix
}

void drawBlur(int times, float inc)
{
    float spost = 0.0f;             // Starting texture coordinates
    float alphainc = 0.9f / times;  // Fade speed for blending
    float alpha = 0.2f;             // Starting alpha

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, blur_texture);

    ViewOrtho();

    alphainc = alpha / times;
    glBegin(GL_QUADS);
        for (uint i=0; i<times; ++i)
        {
            glColor4f(1.0f, 1.0f, 1.0f, alpha);
            glTexCoord2f(0+spost, 1-spost);
            glVertex2f(0,0);

            glTexCoord2f(0+spost, 0+spost);
            glVertex2f(0, HEIGHT);

            glTexCoord2f(1-spost, 0+spost);
            glVertex2f(WIDTH, HEIGHT);

            glTexCoord2f(1-spost, 1-spost);
            glVertex2f(WIDTH, 0);

            spost += inc;
            alpha -= alphainc;
        }
    glEnd();

    ViewPerspective();

    glEnable(GL_DEPTH_TEST);                    // Enable Depth Testing
    glDisable(GL_TEXTURE_2D);                   // Disable 2D Texture Mapping
    glDisable(GL_BLEND);                        // Disable Blending
    glBindTexture(GL_TEXTURE_2D,0);                 // Unbind The Blur Texture
}
void dcLevel::render(float delta)
{

    endless_.render(delta);
    spawner_.render(delta);
        glPushMatrix();
//        renderToTexture();
        glColor3f(0.2f,0.2f,0.2f);
        glPushMatrix();
            Vec3f pos = ship_.getPos().getVec3f();
            glTranslatef(pos.x+ship_.jitter, pos.y+ship_.jitter, pos.z);
            glRotatef(fmod(ship_.getPos().degree+90.0f, 360.0f), 0.0f, 0.0f, 1.0f);
//            renderToTexture();
            particles_.render(delta);
            ship_.render(delta);
//            drawBlur(25, 0.02f);
        glPopMatrix();
    glPopMatrix();

    // Render UI


}
