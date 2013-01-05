/**
 * Wrapper class for Texture classes, common interface .. etc
 */
#ifndef CTEXTUREWRAPPER_H
#define CTEXTUREWRAPPER_H

#include <SDL2/SDL_opengl.h>
#include "global_inc.hpp"

#define INVALID_ID GL_INVALID_VALUE

namespace GFX
{
    class cTextureWrapper
    {
    public:
        cTextureWrapper() : m_TextureWidth(0), m_TextureHeight(0)
                          , m_BytesPerPixel(0), m_TextureFormat(0)
                          , m_u(0.0f), m_v(0.0f), m_u2(1.0f), m_v2(1.0f)
                          , m_TextureID(0)
                          {
                          }
        void        BindGL() const;
        void        FlipTexture(bool flipx, bool flipy);
        const int GetTextureWidth() const;
        const int GetTextureHeight() const;
        const GLint GetBytesPerPixel() const;
        const GLenum GetTextureFormat() const;
        const GLuint GetID() const;
        const float GetU() const;
        const float GetV() const;
        const float GetU2() const;
        const float GetV2() const;
        const void GetUV(float& u, float& v, float& u2, float& v2) const;
        const float GetDeltaU() const;
        const float GetDeltaV() const;
        void SetUV(float u, float v, float u2, float v2);
        void SetTextureID(GLuint texID);
        void SetTextureWidth(float w);
        void SetTextureHeight(float h);
        void SetBytesPerPixel(GLint bbp);
        void SetTextureFormat(GLenum format);

    protected:
        int m_TextureWidth, m_TextureHeight;
        GLint m_BytesPerPixel;
        GLenum m_TextureFormat;
        float m_u, m_v, m_u2, m_v2;
        GLuint m_TextureID;

    }; // End class cTextureWrapper

    inline void cTextureWrapper::BindGL() const
    { glBindTexture(GL_TEXTURE_2D, m_TextureID); }

    inline void cTextureWrapper::FlipTexture(bool flipx, bool flipy)
    {
        if (flipx)
            MATH::swapf(m_u, m_u2);
        if (flipy)
            MATH::swapf(m_v, m_v2);
    }

    inline const int cTextureWrapper::GetTextureWidth() const
    { return m_TextureWidth; }

    inline const int cTextureWrapper::GetTextureHeight() const
    { return m_TextureHeight; }

    inline const GLint cTextureWrapper::GetBytesPerPixel() const
    { return m_BytesPerPixel; }

    inline const GLenum cTextureWrapper::GetTextureFormat() const
    { return m_TextureFormat; }

    inline const GLuint cTextureWrapper::GetID() const
    { return m_TextureID; }

    inline const void cTextureWrapper::GetUV(float& u, float& v, float& u2, float& v2) const
    {
        u = m_u;
        v = m_v;
        u2 = m_u2;
        v2 = m_v2;

    }

    inline const float cTextureWrapper::GetU() const
    { return m_u; }

    inline const float cTextureWrapper::GetV() const
    {
        return m_v;
    }

    inline const float cTextureWrapper::GetU2() const
    { return m_u2; }

    inline const float cTextureWrapper::GetV2() const
    {
        return m_v2;
    }

    inline const float cTextureWrapper::GetDeltaU() const
    { return m_u2 - m_u;}

    inline const float cTextureWrapper::GetDeltaV() const
    {
        return m_v2 - m_v;
    }

    inline void cTextureWrapper::SetUV(float u, float v, float u2, float v2)
    {
        m_u = u;
        m_v = v;
        m_u2 = u2;
        m_v2 = v2;
    }
    inline void cTextureWrapper::SetTextureID(GLuint texID)
    { m_TextureID = texID; }
    inline void cTextureWrapper::SetTextureWidth(float w)
    { m_TextureWidth = w; }
    inline void cTextureWrapper::SetTextureHeight(float h)
    { m_TextureHeight = h; }
    inline void cTextureWrapper::SetBytesPerPixel(GLint bbp)
    { m_BytesPerPixel = bbp; }
    inline void cTextureWrapper::SetTextureFormat(GLenum format)
    { m_TextureFormat = format; }
} // End namespace GFX
#endif // CTEXTUREWRAPPER_H
