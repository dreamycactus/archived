#ifndef DCLEVEL_H
#define DCLEVEL_H

#include "dcShip.h"
#include "dcTunnelStrip.h"
#include "dcRailPos.h"
#include "dcSpawner.h"
#include "CParticleManager.h"

class dcLevel
{
    public:
        dcLevel();
        virtual ~dcLevel();

        void    init();
        void    handleInput(float delta);
        void    tick(float delta);
        void    render(float delta);
        void                    renderToTexture();

        float    getShipDepth() { return ship_.getPos().depth; }
        dcShip              ship_;
    private:
            // Game var

        dcTunnelStrip       endless_; //!< Tunnel
        dcTunnel            tunnel_;
        dcSpawner           spawner_;
        CParticleManager    particles_;

};

#endif // DCLEVEL_H
