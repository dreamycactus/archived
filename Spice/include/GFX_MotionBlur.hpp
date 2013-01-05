#ifndef GFX_MOTIONBLUR_H
#define GFX_MOTIONBLUR_H

#include "global_inc.hpp"
#include "GFX_TextureUtilities.hpp"

namespace GFX
{
    enum { MIPMAPPED, NEAREST };
    bool CreateMotionBlurTexture(cTextureWrapper& tex, int width, int height, int interpolation);
}



#endif // GFX_MOTIONBLUR_H
