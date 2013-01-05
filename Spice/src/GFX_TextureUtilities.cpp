#include "GFX_TextureUtilities.hpp"
#include "GFX_cTextureWrapper.hpp"
#include "MATH_Math.hpp"

namespace GFX
{

    void ImmediateRenderTexturePos2Dim2(const cTextureWrapper& tex, float x, float y, float w, float h)
    {
        const float u   = tex.GetU();
        const float v   = tex.GetV();
        const float u2  = tex.GetU2();
        const float v2  = tex.GetV2();

        const float x2 = x+w;
        const float y2 = y+h;

        glBindTexture(GL_TEXTURE_2D, tex.GetID());               // Select Our Texture

        glBegin(GL_QUADS);
            glTexCoord2f(u, v);     glVertex3f(x,  y,  1.0f);
            glTexCoord2f(u2, v);    glVertex3f(x2,  y,  1.0f);
            glTexCoord2f(u2, v2);   glVertex3f(x2, y2,  1.0f);
            glTexCoord2f(u, v2);    glVertex3f(x, y2,  1.0f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ImmediateRenderTexturePos2Dim2Origin2Scale2Rot(const cTextureWrapper& tex, float x, float y, float w, float h
                                               , float x_origin, float y_origin
                                               , float x_scale, float y_scale, float rot_degrees)
    {
        const float x_world = x + x_origin;
        const float y_world = y + y_origin;
        const float fx = -x_origin * x_scale;
        const float fy = -y_origin * y_scale;
        const float fx2 = (w - x_origin) * x_scale;
        const float fy2 = (h - y_origin) * y_scale;

        const float p1x = fx;
        const float p1y = fy;
        const float p2x = fx2;
        const float p2y = fy;
        const float p3x = fx2;
        const float p3y = fy2;
        const float p4x = fx;
        const float p4y = fy2;

        float x1 = p1x;
        float y1 = p1y;
        float x2 = p2x;
        float y2 = p2y;
        float x3 = p3x;
        float y3 = p3y;
        float x4 = p4x;
        float y4 = p4y;

        if (!MATH::CloseTof(rot_degrees, 0.0f)) {
            const float cos_v = MATH::cos_deg(rot_degrees);
            const float sin_v = MATH::sin_deg(rot_degrees);

            x1 = cos_v * p1x - sin_v * p1y;
            y1 = sin_v * p1x + cos_v * p1y;

            x2 = cos_v * p2x - sin_v * p2y;
            y2 = sin_v * p2x + cos_v * p2y;

            x3 = cos_v * p3x - sin_v * p3y;
            y3 = sin_v * p3x + cos_v * p3y;

            x4 = x1 + (x3 - x2); // < Interesting!
            y4 = y3 - (y2 - y1);
        }
        x1 += x_world;
        y1 += y_world;
        x2 += x_world;
        y2 += y_world;
        x3 += x_world;
        y3 += y_world;
        x4 += x_world;
        y4 += y_world;

        const float u   = tex.GetU();
        const float v   = tex.GetV();
        const float u2  = tex.GetU2();
        const float v2  = tex.GetV2();

        glBindTexture(GL_TEXTURE_2D, tex.GetID());               // Select Our Texture

        glBegin(GL_QUADS);
            glTexCoord2f(u, v);     glVertex3f(x1,  y1,  1.0f);
            glTexCoord2f(u2, v);    glVertex3f(x2,  y2,  1.0f);
            glTexCoord2f(u2, v2);   glVertex3f(x3, y3,  1.0f);
            glTexCoord2f(u, v2);    glVertex3f(x4, y4,  1.0f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Generate texture routine taken from Full Scene Motion Blur By Stanciu Vlad
    bool GenerateTexture(GLuint &Texture, int SizeX, int SizeY, int Channels, int Format, int Min_Filter, int Mag_Filter)
    {
        bool Status = false;
        unsigned int memoryRequiredSize = SizeX * SizeY * Channels;

        unsigned int *memoryBlock = new unsigned int[memoryRequiredSize];
        if(memoryBlock == 0)
            return Status;

        ZeroMemory(memoryBlock, memoryRequiredSize);

        Status = GenerateTexture(Texture, SizeX, SizeY, Channels, Format, Min_Filter, Mag_Filter, memoryBlock);
        delete [] memoryBlock;

    //    int ErrorStatus = glGetError();
    //    if(ErrorStatus == GL_NO_ERROR)
    //        Status = TRUE;

        return Status;
    }

    bool GenerateTexture(GLuint &Texture, int SizeX, int SizeY, int Channels, int Format, int Min_Filter, int Mag_Filter, unsigned int *memoryArea)
    {
        bool Status = false;

        if(memoryArea == 0)
            return Status;

        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

        //gluBuild2DMipmaps(GL_TEXTURE_2D, Channels, SizeX, SizeY, Format, GL_UNSIGNED_INT, memoryBlock);
        glTexImage2D(GL_TEXTURE_2D, 0, Channels, SizeX, SizeY, 0, Format, GL_UNSIGNED_INT, memoryArea );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Min_Filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mag_Filter);


    //    int ErrorStatus = glGetError();
    //    if(ErrorStatus == GL_NO_ERROR)
    //        Status = TRUE;

        return Status;
    }

    void RenderFullViewportTexture(cTextureWrapper& tex, int viewportWidth, int viewportHeight)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
                glLoadIdentity();
                glOrtho(0.0, (GLdouble)viewportWidth, 0.0, (GLdouble)viewportHeight, -10.0, 10.0);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                ImmediateRenderTexturePos2Dim2(tex, 0.0f, 0.0f
                                            , static_cast<float>(viewportWidth)
                                            , static_cast<float>(viewportHeight));

                glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    void CopyBackbufferToTexture(cTextureWrapper& tex, int width, int height)
    {
        glBindTexture(GL_TEXTURE_2D, tex.GetID());
        glCopyTexImage2D(GL_TEXTURE_2D, 0, tex.GetTextureFormat(), 0, 0, (GLsizei)width, (GLsizei)height, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
