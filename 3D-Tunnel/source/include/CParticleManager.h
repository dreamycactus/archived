// Include Guard
#ifndef CPARTICLEMANAGER_H
#define CPARTICLEMANAGER_H

// Headers
#include "dcMath.h"
#include "mytypes.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

class Matrix3;
struct TElem
{
    TElem() { next = 0; }
    int index;
    TElem* next;
};

class CParticleManager
{
    public:
                enum            { MAX_PARTICLES = 1000 };
                Vec3f           spawn_location;
                bool            safety;

    // Methods
                                CParticleManager();
    virtual                     ~CParticleManager();

                void            init();
                void            initNormals(uint i);
                void            tick(float delta);
                void            render(float delta);
                void            reset();

                void            setForce(const Vec3f& g, bool reset = true);
                void            setFriction(float f) { FRICTION = f; }
                void            setParticleColour(uint i, float r, float g, float b, float a=0.0f);
                void            setParticlePos(uint i, const Vec3f& p);
                void            setParticleSize(uint i, float sz);
                void            spawnParticle(uint i);
                void            killParticle(uint i);
                void            rotateParticle(uint i, const Matrix3& m);
                void            explode(const Vec3f& pos, int count=100);
    private:
    // Members
                GLuint          vbos_[3];

                Vec3f           pos[MAX_PARTICLES*24] ;     //!< Vertex of quad for particles
                Vec3f           normal[MAX_PARTICLES*24] ;  //!< Vertex of quad for particles
                dcColour        colour[MAX_PARTICLES*24];
                float           dim[MAX_PARTICLES];         //!< Particle size

                Vec3f           vel[MAX_PARTICLES];
                Vec3f           accel[MAX_PARTICLES];
                float           life[MAX_PARTICLES];

                TElem           pool_[MAX_PARTICLES];       //!< Pool to keep track of particles
                TElem*          first_free_;                //!< First element in linked list that is free

          const float   SPEW_RATE;
                float   FRICTION;
};

#endif // CPARTICLEMANAGER_H
