#include "CParticleManager.h"

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "math/dcRandom.h"
#include "graphics/dcVBO.h"

#include <iostream>
using std::cout;


CParticleManager::CParticleManager() : SPEW_RATE(2.0f), FRICTION(0.3f)
{
    //ctor
}

CParticleManager::~CParticleManager()
{
    dcVBO::DeleteBuffersARB(3, &vbos_[0]);
}

void initVBO()
{
}

void CParticleManager::initNormals(uint i)
{
    for (uint j=0; j<24; ++j)
    {
        normal[i*24+j].zero();
        if (j < 4)       { normal[i*24+j].z = 1.0f;  }
        else if (j < 8)  { normal[i*24+j].x = 1.0f;  }
        else if (j < 12) { normal[i*24+j].y = 1.0f;  }
        else if (j < 16) { normal[i*24+j].x = -1.0f; }
        else if (j < 20) { normal[i*24+j].y = -1.0f; }
        else if (j < 24) { normal[i*24+j].z = -1.0f; }

    }
}

void CParticleManager::init()
{
    initVBO();

    reset();
            // Init the VBOs
    dcVBO::GenBuffersARB(3, &vbos_[0]);

    // color
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbos_[0]);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*24)*4*sizeof(float), colour, GL_STREAM_DRAW_ARB);

    // vertices
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbos_[1]);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*24)*3*sizeof(float), pos, GL_STREAM_DRAW_ARB);

    // normals
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbos_[2]);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*24)*3*sizeof(float), normal, GL_STREAM_DRAW_ARB);
}



#define SPREAD 0.1f
void CParticleManager::spawnParticle(uint i)
{
    setParticleSize(i, dcRandom::randFloat(0.05f, 0.07f));
    setParticleColour(i, 1.0f, 1.0f, 1.0f, 1.0f);

    life[i] = dcRandom::randFloat(0.2f, 0.5f);

    setParticlePos(i, spawn_location);
    initNormals(i);

    vel[i].x = dcRandom::randFloat(-SPREAD, SPREAD);
    vel[i].y = dcRandom::randFloat(-SPREAD, SPREAD);
    vel[i].z = dcRandom::randFloat(3.5f, 5.5f);
}

void CParticleManager::killParticle(uint i)
{
    setParticleSize(i, 0.0f);
    setParticleColour(i, 0.0f, 0.0f, 0.0f, 0.0f);
    setParticlePos(i, Vec3f(0.0f,0.0f,400.0f));

    life[i] = 0.0f;
}

void CParticleManager::rotateParticle(uint i, const Matrix3& m)
{
}

void CParticleManager::reset()
{
    safety = true;
    first_free_ = 0;
    for (uint i=0; i<MAX_PARTICLES; ++i)
    {
        // Setup
        spawnParticle(i);
        killParticle(i);
        initNormals(i);

        if (i==MAX_PARTICLES-1) { continue; }

        // Pool init
        pool_[i].index  = i;
        pool_[i].next   = &pool_[i+1];

    }
    pool_[MAX_PARTICLES-1].index = MAX_PARTICLES-1;
    pool_[MAX_PARTICLES-1].next = 0;
    first_free_     = &pool_[0];

//    setForce(Vec3f(0.0f, -0.0f, 0.08f));

}
void CParticleManager::tick(float delta)
{
    // Spawn particles
    int spawn_count = (int)(clamp(delta/SPEW_RATE, 0.0f, 1.0f));
    cout << delta << "," << spawn_count<< "\n";

    if (!safety) { spawn_count = 500; }

    while (spawn_count-- > 0 && first_free_)
    {
        spawnParticle(first_free_->index);
        first_free_ = first_free_->next;
    }

    float rate = 0.01f;

    Matrix3 m = Matrix3();
    m.rotX(0.1f*delta);

    for (uint i=0; i<MAX_PARTICLES; ++i)
    {
        life[i] -= delta*0.001f;
        if (life[i] <= 0.0f) // If particle is dead
        {
            killParticle(i);
            pool_[i].next = first_free_;
            first_free_ = &pool_[i];
            continue;
        }

        setParticleColour(i, life[i]/4.0f, 0.0f, life[i]*2.0f, life[i]*2.0f);
        vel[i]      += accel[i] * delta * rate;

        //rotateParticle(i, m);
        Vec3f mid = (pos[24*i+0]+pos[24*i+16])/2.0f;
        for (uint j=0; j<24; ++j)
        {
            pos[24*i+j] += vel[i] * delta * rate;
            pos[24*i+j].transform(pos[24*i+j] - mid, m, mid);
            normal[24*i+j].transform(Vec3f(normal[24*i+j]), m, Vec3f(0.0f,0.0f,0.0f));
        }
        // Collision
        float height = pos[24*i+0].y - spawn_location.y;
        if (height<-0.0f && fabs(pos[24*i+0].z)<10.0f && fabs(pos[24*i+0].x)<10.0f)
        {
            for (uint j=0; j<24; ++j)
            {
                pos[24*i+j].y -= height;
            }
            vel[i].y *= -1.0f*FRICTION;
            vel[i].x *= FRICTION;
            vel[i].z *= FRICTION;
        }
    }
}

void CParticleManager::render(float delta)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0);
     // For VBOs
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // bind color
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbos_[0]);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*24)*4*sizeof(float), colour);
    glColorPointer(4, GL_FLOAT, 0, 0);

    // bind vertices [these are quads]
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbos_[1]);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*24)*3*sizeof(float), pos);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // bind normals
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbos_[2]);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*24)*3*sizeof(float), normal);
    glNormalPointer(GL_FLOAT, 0, 0);

    // Alphas stuffs
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    // Draw vbos
    glDrawArrays(GL_QUADS, 0, MAX_PARTICLES*24);

    glDisable(GL_BLEND);

    // Disable VBO
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // Release VBO
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void CParticleManager::explode(const Vec3f& pos, int count)
{
    const static float AMOUNT = 1.0f;
    while (count-- > 0 && first_free_)
    {
        spawnParticle(first_free_->index);
        vel[first_free_->index].x = dcRandom::randFloat(-AMOUNT, AMOUNT);
        vel[first_free_->index].y = dcRandom::randFloat(-AMOUNT, AMOUNT);
        vel[first_free_->index].z = dcRandom::randFloat(-AMOUNT, AMOUNT);
        first_free_ = first_free_->next;
    }
}

void CParticleManager::setForce(const Vec3f& g, bool reset)
{
    for (uint i=0; i<MAX_PARTICLES; ++i)
    {
        if (reset) { accel[i].zero(); }
        accel[i] += g;
    }
}
void CParticleManager::setParticleColour(uint i, float r, float g, float b, float a)
{
    if (i < 0 || i > MAX_PARTICLES) { return; }

    for (uint j=0; j<24; ++j)
    {
        colour[(i*24)+j].r = r;
        colour[(i*24)+j].g = g;
        colour[(i*24)+j].b = b;
        colour[(i*24)+j].a = a;
    }
}

void CParticleManager::setParticleSize(uint i, float sz)
{
    if (i < 0 || i > MAX_PARTICLES) { return; }

    dim[i] = sz;
}

void CParticleManager::setParticlePos(uint i, const Vec3f& p)
{
    if (i < 0 || i > MAX_PARTICLES) { return; }

    // P0
    pos[(i*24)+0].x = p.x + dim[i];
    pos[(i*24)+0].y = p.y + dim[i];
    pos[(i*24)+0].z = p.z + dim[i];

    // P1
    pos[(i*24)+1].x = p.x - dim[i];
    pos[(i*24)+1].y = p.y + dim[i];
    pos[(i*24)+1].z = p.z + dim[i];

    // P2
    pos[(i*24)+2].x = p.x - dim[i];
    pos[(i*24)+2].y = p.y - dim[i];
    pos[(i*24)+2].z = p.z + dim[i];

    // P3
    pos[(i*24)+3].x = p.x + dim[i];
    pos[(i*24)+3].y = p.y - dim[i];
    pos[(i*24)+3].z = p.z + dim[i];

    //-------------------------------

    // P4
    pos[(i*24)+4].x = p.x + dim[i];
    pos[(i*24)+4].y = p.y + dim[i];
    pos[(i*24)+4].z = p.z + dim[i];

    // P5
    pos[(i*24)+5].x = p.x + dim[i];
    pos[(i*24)+5].y = p.y - dim[i];
    pos[(i*24)+5].z = p.z + dim[i];

    // P6
    pos[(i*24)+6].x = p.x + dim[i];
    pos[(i*24)+6].y = p.y - dim[i];
    pos[(i*24)+6].z = p.z - dim[i];

    // P7
    pos[(i*24)+7].x = p.x + dim[i];
    pos[(i*24)+7].y = p.y + dim[i];
    pos[(i*24)+7].z = p.z - dim[i];

    //-------------------------------

    // P8
    pos[(i*24)+8].x = p.x + dim[i];
    pos[(i*24)+8].y = p.y + dim[i];
    pos[(i*24)+8].z = p.z + dim[i];

    // P9
    pos[(i*24)+9].x = p.x + dim[i];
    pos[(i*24)+9].y = p.y + dim[i];
    pos[(i*24)+9].z = p.z - dim[i];

    // P10
    pos[(i*24)+10].x = p.x - dim[i];
    pos[(i*24)+10].y = p.y + dim[i];
    pos[(i*24)+10].z = p.z - dim[i];

    // P11
    pos[(i*24)+11].x = p.x - dim[i];
    pos[(i*24)+11].y = p.y + dim[i];
    pos[(i*24)+11].z = p.z + dim[i];

    //-------------------------------

    // P12
    pos[(i*24)+12].x = p.x - dim[i];
    pos[(i*24)+12].y = p.y + dim[i];
    pos[(i*24)+12].z = p.z + dim[i];

    // P13
    pos[(i*24)+13].x = p.x - dim[i];
    pos[(i*24)+13].y = p.y + dim[i];
    pos[(i*24)+13].z = p.z - dim[i];

    // P14
    pos[(i*24)+14].x = p.x - dim[i];
    pos[(i*24)+14].y = p.y - dim[i];
    pos[(i*24)+14].z = p.z - dim[i];

    // P15
    pos[(i*24)+15].x = p.x - dim[i];
    pos[(i*24)+15].y = p.y - dim[i];
    pos[(i*24)+15].z = p.z + dim[i];

    //-------------------------------

    // P16
    pos[(i*24)+16].x = p.x - dim[i];
    pos[(i*24)+16].y = p.y - dim[i];
    pos[(i*24)+16].z = p.z - dim[i];

    // P17
    pos[(i*24)+17].x = p.x + dim[i];
    pos[(i*24)+17].y = p.y - dim[i];
    pos[(i*24)+17].z = p.z - dim[i];

    // P18
    pos[(i*24)+18].x = p.x + dim[i];
    pos[(i*24)+18].y = p.y - dim[i];
    pos[(i*24)+18].z = p.z + dim[i];

    // P19
    pos[(i*24)+19].x = p.x - dim[i];
    pos[(i*24)+19].y = p.y - dim[i];
    pos[(i*24)+19].z = p.z + dim[i];

    //-------------------------------

    // P20
    pos[(i*24)+20].x = p.x + dim[i];
    pos[(i*24)+20].y = p.y - dim[i];
    pos[(i*24)+20].z = p.z - dim[i];

    // P21
    pos[(i*24)+21].x = p.x - dim[i];
    pos[(i*24)+21].y = p.y - dim[i];
    pos[(i*24)+21].z = p.z - dim[i];

    // P22
    pos[(i*24)+22].x = p.x - dim[i];
    pos[(i*24)+22].y = p.y + dim[i];
    pos[(i*24)+22].z = p.z - dim[i];

    // P23
    pos[(i*24)+23].x = p.x + dim[i];
    pos[(i*24)+23].y = p.y + dim[i];
    pos[(i*24)+23].z = p.z - dim[i];

}
