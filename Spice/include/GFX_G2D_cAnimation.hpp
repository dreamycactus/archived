// CAnimation class based on the same from libgdx

#ifndef CANIMATION_H
#define CANIMATION_H

#include <vector>
#include "MATH_MathHelper.hpp"
#include "GFX_cTextureWrapper.hpp"

namespace GFX
{
    class cTextureWrapper;
    namespace G2D
    {
        class cAnimation
        {
        public:
            cAnimation();
            cAnimation(float ticks_per_frame, std::vector<cTextureWrapper> frames);

            virtual ~cAnimation();

            void ClearAll();
            void PushFrame(const cTextureWrapper& frame);

            const cTextureWrapper& GetKeyFrame(float statetime, bool is_looping) const;
            const cTextureWrapper& operator[](int i) const;

            // Setters
            void SetTicksPerFrame(float tpf);

        private:
            std::vector<cTextureWrapper> m_Frames;
            float m_TicksPerFrame;
            float m_TotalTicks;
        };  // End class cAnimation

        inline const cTextureWrapper& cAnimation::GetKeyFrame(float statetime, bool is_looping) const
        {
            int frame_index = static_cast<int>(statetime/m_TicksPerFrame);

            if (is_looping) {
                frame_index %= m_Frames.size();
            } else {
                frame_index = MATH::minf(frame_index, m_Frames.size()-1);
            }
            return m_Frames[frame_index];
        }
        inline const cTextureWrapper& cAnimation::operator[](int i) const
        {
            return m_Frames[i];
        }
    }   // End namespace G2D
}   // End namespace GFX


#endif // CANIMATION_H
