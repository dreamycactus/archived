#ifndef DCENEMY_H
#define DCENEMY_H

#include <boost/shared_ptr.hpp>
#include "tokens/CMesh.h"
#include "dcRailPos.h"
#include "dcEntity.h"

class dcEnemy : public dcEntity
{
    public:
        dcEnemy();
        virtual ~dcEnemy();
        void tick(float delta);
        void render(float delta);
        void setMesh(shared_ptr<CMesh> m) { meshy = m; }
        void kill();
        dcColour colour;
    private:
    shared_ptr<CMesh> meshy;
};

#endif // DCENEMY_H
