////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CPointState.h
 * \author  Hua Fei Yu 0951402
 * \date    September 22, 2011
 * \brief   State for drawing points
 */
////////////////////////////////////////////////////////////////////////////////
#ifndef CPOINTSTATE_H
#define CPOINTSTATE_H

// Headers
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "IGameState.h"
#include "misc/CParticle.h"
#include "mytypes.h"
#include "camera/CCamera.h"
#include "tokens/CMaterial.h"
#include "CParticleManager.h"
#include "dcLevel.h"
#include "dcTunnel.h"


using std::vector;

class Vector3;
class CTimer;


class CPointState : public IGameState
{
    public:
                                CPointState(int w, int h);
    virtual                     ~CPointState();

            void                init();
            void                tick(float delta);
            void                render(float delta);
            void                cleanup();


    private:
            enum { NUM_PARTICLES = 100 };
            int                 mode_;
            bool                lighting_;
            CMaterial           material_;
            CCamera             cam_;
            float               ang_x_, ang_y_;

        // Private method
            void                handleInput();
            void                updateCamera(float delta);
            void                GetMovementDirection(Vec3f& direction);
            bool                withinBounds(int x, int y);

            const int           WIDTH, HEIGHT;

            bool                paused_;

            dcLevel             level_;
            dcTunnel            tun;



};

#endif // CPOINTSTATE_H
