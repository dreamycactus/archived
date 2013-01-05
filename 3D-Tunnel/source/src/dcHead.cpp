#include "dcHead.h"
#include "CObjMeshParser.h"
#include "CParticleManager.h"
dcHead::dcHead(): dcEntity(), meshy(new CMesh)
{
    active_ = true;
}

dcHead::~dcHead()
{
    //dtor
}


void dcHead::tick(float delta)
{
    const float rate = 1.0f;
    angle_ += rate*delta;
}

void dcHead::render(float delta)
{
    glColor4fv(&colour.r);
    meshy->render();
}

void dcHead::kill()
{
    active_ = false;
    particles->explode(pos);
}

