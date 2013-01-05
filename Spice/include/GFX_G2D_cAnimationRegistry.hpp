#ifndef CANIMATIONREGISTRY_H
#define CANIMATIONREGISTRY_H

#include "global_inc.hpp"
#include "GFX_G2D_cAnimation.hpp"

namespace CORE
{
    class cGame;
}


namespace GFX
{
    namespace G2D
    {
        class cAnimationRegistry
        {
        public:
            cAnimationRegistry();
            virtual ~cAnimationRegistry();

            void PushAnimation(GFX::G2D::cAnimation anim);
            GFX::G2D::cAnimation& GetAnimation(int i);

            void UpdateCurrent(float delta);
            void ResetStatetime() { m_Statetime=0.0f;}
            void Render(CORE::cGame& game, float delta);

            GFX::G2D::cAnimation& operator[](int i)
            { return m_Anims[i]; }

            const cTextureWrapper& GetCurrentFrame()
            { return m_Anims[m_CurrentIndex].GetKeyFrame(m_Statetime, true); }

            int GetCurrentIndex()
            { return m_CurrentIndex; }
            float GetStatetime()
            { return m_Statetime; }
            void SetTicksPerFrame(int tpf)
            { m_TicksPerFrame = tpf; }
            void SetCurrentIndex(int i)
            { m_CurrentIndex = i; }
            void SetStatetime(float t)
            { m_Statetime = t; }

            void Reset();
        private:
            std::vector<GFX::G2D::cAnimation> m_Anims;
            std::vector<bool> m_Loops;
            int m_CurrentIndex;
            float m_Statetime;
            float m_TicksPerFrame;

        };
    }
}
#endif // CANIMATIONREGISTRY_H
