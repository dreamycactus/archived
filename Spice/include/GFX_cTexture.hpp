/**
 * Texture class taken from The OpenGL Object Loader project
 */

#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <memory>
#include <cassert>
#include <string>
#include "GFX_cTextureWrapper.hpp"

using std::string;


namespace GFX
{
    // Forward declarations
    class cImage;

    class cTexture : public cTextureWrapper
    {
    public:
        cTexture(const string& str_filepath);
        // Require texture dimension to be power of two for < OGL 2.0 versions
        virtual ~cTexture();

        const bool	operator==(const cTexture& rhs) const;

        const bool	IsTransparent() const    { return m_is_transparent; }
        const bool	IsRegistered() const     { return m_pImage.get() == 0; }
        void	    RegisterGL();

        inline void	CheckTexture() const;
            //  REQUIRE: (pImage is not NULL) OR (the texture has been passed to OpenGL)
    private:
        bool m_is_transparent;
        std::shared_ptr<cImage> m_pImage;
    }; // End class cTexture

    inline void cTexture::CheckTexture() const
    { assert( m_TextureID != INVALID_ID); }

} // End namespace GFX

#endif // CTEXTURE_H
