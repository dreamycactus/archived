#include "dcTunnelStrip.h"
#include "dcRailPos.h"
#include "dcSpawner.h"
#include "math/dcRandom.h"
#include "graphics/shapes.h"

dcTunnelStrip::dcTunnelStrip()
{
}

dcTunnelStrip::~dcTunnelStrip()
{
    //dtor
}

void dcTunnelStrip::init()
{

    MAX_SEGMENTS    = 400;
    CIRCLE_SLICES   = 8;
    RADIUS          = 9.0f;
    SEGMENT_LENGTH  = 10.0f;
    dcRailPos::radius = 6.7f;

    tunnels_[0].init(CIRCLE_SLICES, MAX_SEGMENTS, RADIUS, SEGMENT_LENGTH);
    tunnels_[0].setColour(dcColour(0.2f,0.2f,0.2f, 1.0f));
    tunnels_[1].init(CIRCLE_SLICES, MAX_SEGMENTS, RADIUS, SEGMENT_LENGTH);
    tunnels_[1].setColour(dcColour(0.5f,0.1f,0.1f, 0.9f));

    respecTunnel(0);
    respecTunnel(1);
    tunnel_depth_ = 0.0f;

    index_ = 0;
    render_both_ = false;

    dcRandom::init();
    spawner = 0;
}

void dcTunnelStrip::tick(float delta, float cam_pos_z)
{
    if (!isInTunnel(cam_pos_z-2.0f)) // If cam is in next tunnel
    {
        render_both_ = false;
        tunnel_depth_ -= tunnels_[index_].SEGMENT_LENGTH*tunnels_[index_].LENGTHWISE_SLICES;
        respecTunnel(index_);
        index_ = (index_+1) % 2;
        spawner->spawnMany(tunnel_depth_, tunnel_depth_-tunnels_length_[index_], RADIUS-2.0f, dcRandom::randInt(10, 50));
    }
    else if (!isInTunnel(cam_pos_z-30.0f))   // Else if cam is close to next tunnel
    {
        render_both_ = true;
    }
}

void dcTunnelStrip::render(float delta)
{
    glPushMatrix();
        glTranslatef(0.0f,0.0f,tunnel_depth_);
        glBegin(GL_QUADS);
            glColor3f(1.0f,0.0f,0.0f);
            glVertex3f(-RADIUS,-RADIUS,-tunnels_length_[index_]);
            glVertex3f(RADIUS,-RADIUS,-tunnels_length_[index_]);
            glVertex3f(RADIUS,RADIUS,-tunnels_length_[index_]);
            glVertex3f(-RADIUS,RADIUS,-tunnels_length_[index_]);
        glEnd();
        tunnels_[index_].render();

        if (render_both_)
        {
            glTranslatef(0.0f,0.0f,tunnels_length_[(index_+1)%2]);
             glBegin(GL_QUADS);
                glColor3f(1.0f,0.0f,0.0f);
                glVertex3f(-RADIUS,-RADIUS,-tunnels_length_[(index_+1)%2]);
                glVertex3f(RADIUS,-RADIUS,-tunnels_length_[(index_+1)%2]);
                glVertex3f(RADIUS,RADIUS,-tunnels_length_[(index_+1)%2]);
                glVertex3f(-RADIUS,RADIUS,-tunnels_length_[(index_+1)%2]);
            glEnd();
            tunnels_[(index_+1)%2].render();

        }
    glPopMatrix();
}

bool dcTunnelStrip::isInTunnel(float depth)
{
    if (depth < tunnel_depth_-tunnels_length_[index_]) { return false; }
    return true;
}
void dcTunnelStrip::respecTunnel(int i)
{
    tunnels_[i].LENGTHWISE_SLICES = dcRandom::randInt(10, MAX_SEGMENTS);
    tunnels_[i].recalculateVertexCount();
    tunnels_length_[i] = tunnels_[i].LENGTHWISE_SLICES*tunnels_[i].SEGMENT_LENGTH;
    if (0 != i)
    {
        tunnels_[i].setColour(dcColour(dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.0f, 1.0f),
                                       dcRandom::randFloat(0.3f, 1.0f)));
    }

}
