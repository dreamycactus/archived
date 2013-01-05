#include "GFX_G2D_cAnimationRegistry.hpp"

#include "CORE_cGame.hpp"

using namespace GFX::G2D;

cAnimationRegistry::cAnimationRegistry()
: m_Anims()
, m_CurrentIndex(0)
, m_Statetime(0.0f)
, m_TicksPerFrame(100.0f)
{

}

cAnimationRegistry::~cAnimationRegistry()
{

}

void cAnimationRegistry::PushAnimation(GFX::G2D::cAnimation anim)
{
    m_Anims.push_back(anim);
    m_Anims.back().SetTicksPerFrame(m_TicksPerFrame);

}

void cAnimationRegistry::UpdateCurrent(float delta)
{
    m_Statetime += delta;
    if (m_Statetime > 1000000.0f) m_Statetime = 0.0f;
}

GFX::G2D::cAnimation& cAnimationRegistry::GetAnimation(int i)
{
    return m_Anims[i];
}

void cAnimationRegistry::Reset()
{
    m_Anims.clear();
    m_Statetime = 0.0f;
}
