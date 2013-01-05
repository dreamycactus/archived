#include "dcSpawner.h"
#include "mytypes.h"
#include "CObjMeshParser.h"
#include "math/dcRandom.h"

dcSpawner::dcSpawner()
{
    //ctor
}

dcSpawner::~dcSpawner()
{
    //dtor
}

void dcSpawner::init()
{
    shared_ptr<CMesh> temp_mesh_head(new CMesh());
    shared_ptr<CMesh> temp_mesh_enemy(new CMesh());

    temp_mesh_enemy->setHasTexture(false);
    temp_mesh_head->setHasTexture(false);

    temp_mesh_head->activateColourMaterial();
    temp_mesh_enemy->activateColourMaterial();

    CObjMeshParser::parse(temp_mesh_head, "res/face.obj");
    CObjMeshParser::parse(temp_mesh_enemy, "res/enemy.obj");

    for (uint i=0; i<100; ++i)
    {
        heads_[i].setMesh(temp_mesh_head);
        heads_[i].particles = particles;
        enemies_[i].setMesh(temp_mesh_enemy);
        enemies_[i].particles = particles;
    }
    respecEntities();
    active_num_ = 0;
}

void dcSpawner::respecEntities()
{
    for (uint i=0; i<100; ++i)
    {
        heads_[i].colour = dcColour(dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.3f, 1.0f));
        enemies_[i].colour = dcColour(dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.3f, 1.0f));
    }
}

void dcSpawner::tick(float delta, dcShip& ship)
{
    for (uint i=0; i<active_num_; ++i)
    {
        if (heads_[i].isActive()) { heads_[i].tick(delta); }
        if (enemies_[i].isActive()) { enemies_[i].tick(delta); }
    }
    doCollide(ship, 2.0f);
}

void dcSpawner::render(float delta)
{
    for (uint i=0; i<active_num_; ++i)
    {
        if (heads_[i].isActive())
        {
            glPushMatrix();
                glTranslatef(heads_[i].pos.x,heads_[i].pos.y,heads_[i].pos.z);
                glScalef(0.3f,0.3f,0.3f);
                heads_[i].render(delta);
            glPopMatrix();
        }
        if (enemies_[i].isActive())
        {
            glPushMatrix();
                glTranslatef(enemies_[i].pos.x,enemies_[i].pos.y,enemies_[i].pos.z);
                enemies_[i].render(delta);
            glPopMatrix();
        }
    }
}

void dcSpawner::spawnMany(float start_depth, float end_depth, float radius, int num)
{
    active_num_ = num;
    float radian;
    for (uint i=0; i<num; ++i)
    {
        radian = dcRandom::randFloat(0.0f, 2*PI);
        heads_[i].pos.x = radius * cos(radian);
        heads_[i].pos.y = radius * sin(radian);
        heads_[i].pos.z = dcRandom::randFloat(start_depth, end_depth);

        radian = dcRandom::randFloat(0.0f, 2*PI);
        enemies_[i].pos.x = radius * cos(radian);
        enemies_[i].pos.y = radius * sin(radian);
        enemies_[i].pos.z = dcRandom::randFloat(start_depth, end_depth);
    }
    for (uint i=num; i<100; ++i)
    {
        heads_[i].pos.z = 500.0f;
        enemies_[i].pos.z = 500.0f;
    }
    respecEntities();
}

void dcSpawner::doCollide(dcShip& ship, float radius)
{
    float dist_sq;
    float radius_sq = radius*radius;
    Vec3f pos = ship.getPos().getVec3f();

    for (uint i=0; i<100; ++i)
    {
        dist_sq = (heads_[i].pos-pos)*(heads_[i].pos-pos);
        if (dist_sq<radius_sq && heads_[i].isActive())
        {
            ship.collideHead(heads_[i]);
        }

        dist_sq = (enemies_[i].pos-pos)*(enemies_[i].pos-pos);
        if (dist_sq<radius_sq && enemies_[i].isActive())
        {
            ship.collideEnemy(enemies_[i]);
        }
    }
}
