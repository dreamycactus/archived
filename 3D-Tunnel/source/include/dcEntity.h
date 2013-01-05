#ifndef DCENTITY_H
#define DCENTITY_H

#include "tokens/CMesh.h"
#include "dcRailPos.h"

class CParticleManager;
class dcEntity
{
    public:
        dcEntity() {}
        virtual ~dcEntity() {}
        virtual void tick(float delta) {}
        virtual void render(float delta) = 0;
        virtual void kill() { active_ = false; }
        virtual bool isActive() { return active_; }
        Vec3f pos;
        CParticleManager* particles;
    protected:
        shared_ptr<CMesh> meshy;
        bool active_;
};

#endif // DCENTITY_H
