#ifndef DCSPAWNER_H
#define DCSPAWNER_H

#include "dcMath.h"
#include "dcRailPos.h"
#include <boost/array.hpp>
#include "dcHead.h"
#include "dcEnemy.h"
#include "dcShip.h"

class CParticleManager;

class dcSpawner
{
    public:
        dcSpawner();
        virtual ~dcSpawner();

        void init();
        void respecEntities();
        void tick(float delta, dcShip& ship);
        void render(float delta);

        void spawnMany(float start_depth, float end_depth, float radius, int num);

        void doCollide(dcShip& ship, float radius);
        CParticleManager* particles;
    private:
        boost::array<dcHead, 100> heads_;
        boost::array<dcEnemy, 100> enemies_;
        int active_num_;


};

#endif // DCSPAWNER_H
