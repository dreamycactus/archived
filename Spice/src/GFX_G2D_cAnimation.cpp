/**
 *
 */
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_cTextureWrapper.hpp"

using namespace GFX::G2D;

cAnimation::cAnimation()
{

}
cAnimation::cAnimation(float ticks_per_frame, std::vector<cTextureWrapper> frames)
{
    m_Frames = frames;
    SetTicksPerFrame(ticks_per_frame);
}

cAnimation::~cAnimation()
{
    ClearAll();
}

void cAnimation::ClearAll()
{
    m_Frames.clear();
}
void cAnimation::PushFrame(const GFX::cTextureWrapper& frame)
{
    m_Frames.push_back(frame);
    m_TotalTicks += m_TicksPerFrame;
}

void cAnimation::SetTicksPerFrame(float tpf)
{
    m_TicksPerFrame = tpf;
    m_TotalTicks = m_TicksPerFrame * m_Frames.size();
}
