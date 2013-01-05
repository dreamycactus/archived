/**
 * Texture Region class adapted from libgdx
 */
#ifndef CTEXTUREREGION_H
#define CTEXTUREREGION_H

#include <vector> // TODO: DON'T USE?
#include "GFX_cTextureWrapper.hpp"

namespace GFX
{
    // Forward Declarations
    class cTexture;

    namespace G2D
    {
        class cTextureRegion : public cTextureWrapper
        {
        public:
            // Empty constructor
            cTextureRegion();

            // Creates texture region the whole size of the passed texture
            cTextureRegion(const cTextureWrapper& tex);

            // Creates texture region using offsets, height, and width of the passed texture
            // Negative dimensions indicate flips
            cTextureRegion(const cTextureWrapper& tex, int x_offset, int y_offset, int width, int height);

            // Treating tex as a full texture, this ctor creates texture region using texture mapping coords
            // i.e. uv coords are relative to the tex, not the base texture.
            cTextureRegion(const cTextureWrapper& tex, float u, float v, float u2, float v2);

//            // Creates texture region using offsets, height, and width of the passed texture region
//            // Negative dimensions indicate flips
//            cTextureRegion(const cTextureRegion& tex_reg, int x_offset, int y_offset, int width, int height);

            // Copy constructor
            cTextureRegion(const cTextureRegion& rhs);

            // Assignment


            virtual ~cTextureRegion();

            void CopyTextureWrapper(const cTextureWrapper& rhs);

            // Static functions
            static std::vector<cTextureWrapper> SplitTextureHorizontalTexNumXYWH(const cTextureWrapper& tex, int nFrames, int frameWidth, int frameHeight, int x_offset, int y_offset);
//            static std::vector<cTextureWrapper> SplitTextureRegionHorizontal(const cTextureWrapper& tex_reg, int frame_width, int y_offset);
            //TODO: ADD VERTICAL SPLITS??; USE OWN ARRAY CLASS

            // Getters
            const cTexture& GetTexture() const;

            // Setters
            void SetRegionFromDimensionsTexXYWH(const cTextureWrapper& tex, int x_offset, int y_offset, int width, int height);
            void SetRegionFromWholeTexture(const cTextureWrapper& tex);
//            void SetRegionFromTextureRegion(const cTextureWrapper& tex, int x_offset, int y_offset, int width, int height);
            void SetRegionFromUV(const cTextureWrapper& tex, float u, float v, float u2, float v2);
        protected:
            float aspect_ratio;  //!< Width/Height of region
            cTextureRegion& operator=(const cTextureRegion& rhs);
        };

    }
}

#endif // CTEXTUREREGION_H
