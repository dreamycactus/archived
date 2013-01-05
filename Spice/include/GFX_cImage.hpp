/**
 * cImage class taken from The OpenGL Obj Loader
 */
#ifndef GFX_CIMAGE_H
#define GFX_CIMAGE_H

#include "global_inc.hpp"

using std::string;

namespace GFX
{

    class cImage
    {
    public:
        cImage(const string& str_filepath);
        virtual ~cImage() { }

        bool IsTransparent() const;
        void ConvertPixelFormat();
        const GLint GetWidth() const    { CheckImage(); return m_pSurface->w; }
        const GLint GetHeight() const   { CheckImage(); return m_pSurface->h; }
        const unsigned int GetPixel(int x, int y) const;
        const void* GetPixels() const   { CheckImage(); return m_pSurface->pixels; }
        const GLint GetBytesPerPixel() const { return m_nColors; }
        const GLenum GetTextureFormat() const { return m_TextureFormat; }

        inline void CheckImage() const;
    private:
        cImage(const cImage& rhs);            // Don't implement
        cImage& operator=(const cImage& rhs); // Don't implement

        SDL_Surface* m_pSurface;

        GLint       m_nColors;
        GLenum      m_TextureFormat;

    }; // End class cImage

    void cImage::CheckImage() const  { assert(m_pSurface != 0); }

} // End namespace GFX
#endif // GFX_CIMAGE_H
