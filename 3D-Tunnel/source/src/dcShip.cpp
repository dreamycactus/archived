#include "dcShip.h"
#include "CObjMeshParser.h"
#include "helper.h"
#include "dcHead.h"
#include "dcEnemy.h"
#include "graphics/shapes.h"
#include "CParticleManager.h"

#include <iostream>
using namespace std;

dcShip::dcShip() : meshy(new CMesh)
{
}

dcShip::~dcShip()
{
    //dtor
}

void dcShip::init()
{
    CObjMeshParser::parse(meshy, "res/ship.obj");
    boost::shared_ptr<dcTexture> tex(new dcTexture("res/ship_texture.png"));
    tex->registerGL();
    meshy->setTexture(tex);

    thrust_vel_ = 0.01f;

    pos_.depth = 0.0f;
    pos_.degree = 0.0f;

    vel_.depth = 0.3f;
    vel_.degree = 0.0f;

    vel_decay_ = 0.9f;

    MAX_VEL_DEGREE = 1.4f;
    meshy->activateColourMaterial();

    red_ = green_ = blue_ =0.1f;

    shields_  = 10.0f;
    max_shields_ = 10.0f;
    active_ = true;

    jitter_var_ = 0.0f;

}

void dcShip::tick(float delta)
{
    vel_.degree *= pow(vel_decay_, delta);
    vel_.degree = clamp(vel_.degree, -MAX_VEL_DEGREE, MAX_VEL_DEGREE);
    pos_.degree = fmod(pos_.degree + vel_.degree * delta, 360.0f);
    pos_.depth  -= vel_.depth * min(delta, 1.0f);
//    shields_ += 0.001f * delta;
    jitter_var_ = fmod(jitter_var_ + delta/25.0f, 2.0f*PI);
    jitter = sin(jitter_var_)/8.0f;
    cout << jitter << endl;
}


void dcShip::render(float delta)
{
    glColor4f(red_,green_,blue_, 1.0f);
    meshy->render();


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glColor4f(0.1f, 0.2f, 0.6f, 0.1f*(shields_/max_shields_));
    renderSphere(4.0f, 12, 12);
    glDisable(GL_BLEND);
}



void dcShip::damage(float dmg)
{
    shields_ -= dmg;
    shields_ = clamp(shields_, 0.0f, max_shields_);

}

void dcShip::thrust(TDir dir, float delta)
{
    if (LEFT == dir) { vel_.degree -= thrust_vel_*delta; }
    else             { vel_.degree += thrust_vel_*delta; }
    vel_.degree = clamp(vel_.degree, -MAX_VEL_DEGREE, MAX_VEL_DEGREE);
}

void dcShip::collideHead(dcHead& head)
{
    const static float FACTOR  = 0.0009f;
    red_ += head.colour.r*FACTOR;
    green_ += head.colour.g*FACTOR;
    blue_ += head.colour.b*FACTOR;

    red_ = clamp(red_, 0.0f, 1.0f);
    green_= clamp(green_, 0.0f, 1.0f);
    blue_ = clamp(blue_, 0.0f, 1.0f);

    head.kill();
}

void dcShip::collideEnemy(dcEnemy& enemy)
{
    const static float FACTOR  = 0.0025f;
    red_ -= enemy.colour.r*FACTOR;
    green_ -= enemy.colour.g*FACTOR;
    blue_ -= enemy.colour.b*FACTOR;

    if (shields_<1.0f) { kill(); }
    damage(3.4f);
    enemy.kill();
}

void dcShip::kill()
{
    active_ = false;
    particles->explode(pos_.getVec3f(), 100);
}
