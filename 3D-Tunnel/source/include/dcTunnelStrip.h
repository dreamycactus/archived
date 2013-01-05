#ifndef DCTUNNELSTRIP_H
#define DCTUNNELSTRIP_H


// Headers
#include "dcTunnel.h"
#include "mytypes.h"

class dcSpawner;

class dcTunnelStrip
{
    public:
        dcTunnelStrip();
        virtual ~dcTunnelStrip();

        void init();
        void render(float delta);
        void tick(float delta, float cam_pos_z);

        bool isInTunnel(float depth);
        void respecTunnel(int i);
        float getCurrentDepth() { return tunnel_depth_; }
        float getCurrentTunnelLength() { return tunnels_length_[index_];}
        float getRadius() { return RADIUS; }

        dcSpawner* spawner;
    private:
        dcTunnel tunnels_[2];   // 0 - coloured, 1 is greyscale
        float tunnels_length_[2];
        float tunnel_depth_;
        int index_;     //!< Current tunnel index
        bool render_both_;

        uint MAX_SEGMENTS;
        uint CIRCLE_SLICES;
        float SEGMENT_LENGTH;
        float RADIUS;
};

#endif // DCTUNNELSTRIP_H
