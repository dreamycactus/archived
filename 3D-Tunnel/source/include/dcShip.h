#ifndef DCSHIP_H
#define DCSHIP_H

// Headers
#include "dcMath.h"
#include <boost/shared_ptr.hpp>
#include "tokens/CMesh.h"
#include "dcRailPos.h"

class dcHead;
class dcEnemy;
class CParticleManager;

using boost::shared_ptr;
enum TDir               {LEFT = 0, RIGHT };
class dcShip
{
    public:
                                dcShip();
        virtual                 ~dcShip();

        void                    init();

        void                    tick(float delta);
        void                    render(float delta);

        void                    damage(float dmg);
        void                    thrust(TDir dir, float delta);

        void                    collideHead(dcHead& head);
        void                    collideEnemy(dcEnemy& enemy);
        void                    kill();

        const dcRailPos&        getPos() const { return pos_; }
        shared_ptr<CMesh>&      getMesh() { return meshy; }
        float                   jitter;
        CParticleManager*       particles;

        bool                    active_;
    private:
        shared_ptr<CMesh>       meshy;

        dcRailPos               pos_;
        dcRailPos               vel_;

        float                   vel_decay_;
        float                   thrust_vel_;
        float                   MAX_VEL_DEGREE;

        float                   red_;
        float                   green_;
        float                   blue_;

        float                   shields_;
        float                   shields_decay_;
        float                   max_shields_;

        float                   jitter_var_;


};

#endif // DCSHIP_H
