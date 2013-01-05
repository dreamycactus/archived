#include "dcEnemy.h"
#include "CParticleManager.h"

dcEnemy::dcEnemy() : dcEntity()
{
    active_ = true;
}

dcEnemy::~dcEnemy()
{
    //dtor
}

void dcEnemy::tick(float delta)
{
}

void dcEnemy::render(float delta)
{
    glColor4fv(&colour.r);
    meshy->render();
}

void dcEnemy::kill()
{
    active_ = false;
    particles->explode(pos);
}
