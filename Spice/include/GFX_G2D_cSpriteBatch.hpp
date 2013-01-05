// Based loosely on same class of libgdx

#ifndef CSPRITEBATCH_H
#define CSPRITEBATCH_H

#include <SDL2/SDL_opengl.h> // Needed for GLuint
#include "GFX_Color4.hpp"


namespace GFX
{
    // Forward Declarations
    class cTextureMesh;
    class cTextureWrapper;

    namespace G2D
    {
        class cSpriteBatch
        {
        public:
            cSpriteBatch();
            cSpriteBatch(int nBatch); // Number of draws per batch
            virtual ~cSpriteBatch();

            void Destroy();

            void Begin();
            void End();

            void DrawTexturePos2Dim2(const cTextureWrapper& tex, float x, float y, float w, float h);
            void DrawTexturePos2Dim2Origin2Scale2Rot(const cTextureWrapper& tex, float x, float y, float w, float h
                                   , float x_origin, float y_origin
                                   , float x_scale, float y_scale, float rot_degrees);
            //void DrawTextureRegion(const cTextureWrapper& tex, float x, float y, int src_w, int src_h, float degrees, float scale);
            // TODO -- Add more draws

            // Renders all pending textures to be drawn, without ending the sprite batch
            void Flush();

            // Getters
            bool IsBlendingEnabled();

            // Setters
            void SetBatchSize(int i);
            void SetBlendFunction(int src_func, int dest_func);
            void SetBlending(bool b); // Enable or disable blending. !Flushes batches first.
            void SetColor(float r, float g, float b, float a);

        private:
            // Private methods
            void            ChangeTexture(const cTextureWrapper& tex);
            void            FlushIfNewTextureOrBatchFull(const cTextureWrapper& tex); // Best function name ever...
            void            Initialise(int nBatch);
            void            RenderMesh();

            GLuint          m_VboId;                //!< Vertex buffer object ID
            cTextureMesh*   m_Mesh;
            const cTextureWrapper* m_LastTexture;

            int             m_nMaxBatch;            //!< Number of draws per batch
            int             m_Index;

            Color4          m_CurrentColor;

            bool            m_UseVbo;               //!< Defaults is true
            bool            m_IsDrawing;            //!< Set to true when Begin() is called, and false when End() is.
            bool            m_IsBlendingEnabled;


        };
    }
}



#endif // CSPRITEBATCH_H
