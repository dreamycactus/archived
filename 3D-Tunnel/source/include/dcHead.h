#ifndef DCHEAD_H
#define DCHEAD_H

#include <boost/shared_ptr.hpp>
#include "tokens/CMesh.h"
#include "dcRailPos.h"
#include "dcEntity.h"

class dcHead : public dcEntity
{
    public:
        dcHead();
        virtual ~dcHead();
        void tick(float delta);
        void render(float delta);
        void setMesh(shared_ptr<CMesh> m) { meshy = m; }
        void kill();
        dcColour colour;
    private:
        float angle_;
        shared_ptr<CMesh> meshy;



};

#endif // DCHEAD_H
