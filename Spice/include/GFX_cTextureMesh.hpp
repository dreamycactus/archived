#ifndef CTEXTUREMESH_H
#define CTEXTUREMESH_H

#include <vector>
#include <SDL2/SDL_opengl.h>

namespace GFX
{

    class cTextureMesh
    {
    public:
        struct Vertex
        {
            float pos[2];       //!< x and y coord
            float tex_coord[2]; //!< u and v coord
            float col[4];    //!< rgba // Possible to pack all these into one integer. 4 params -> 8 bits each -> 32 bits
        };

                            cTextureMesh(bool useVbo=true);
                            cTextureMesh(int initial_sz, bool useVbo=true); // Reserve some space in vertex buffer
        virtual             ~cTextureMesh();

        void                Initialise(int initial_sz, bool useVbo);
        void                Destroy();
        void                AddVertex4f(float x, float y, float u, float v);
        void                AddVertex8f(float x, float y, float u, float v
                                      , float r, float g, float b, float a);
        void                AddVertex(const Vertex& vertex);
        void                Render();

        // Getters
        const int*          GetIndexBuffer() const;
        int                 GetIndexByteSize() const;
        int                 GetNumberOfIndicies() const;
        int                 GetNumberOfVerticies() const;

        const Vertex&       GetVertex(int i) const;
        const Vertex*       GetVertexBuffer() const;
        const int           GetVertexByteSize() const;

    private:
        // Private Methods
        void                GenerateVbo();

        GLuint              m_VboId;
        int                 m_nBufferSize;
        bool                m_UseVbo;

        std::vector<Vertex> m_VertexBuffer;
        std::vector<int>    m_IndexBuffer;

    };

    inline void cTextureMesh::AddVertex4f(float x, float y, float u, float v)
    {
        Vertex vertex = {
            x, y,
            u, v,
            1.0f, 1.0f, 1.0f, 1.0f
        };
        AddVertex(vertex);
    }
    inline void cTextureMesh::AddVertex8f(float x, float y, float u, float v
                                        , float r, float g, float b, float a)
    {
        Vertex vertex = {
            x, y,
            u, v,
            r, g, b, a
        };
        AddVertex(vertex);
    }

    inline void cTextureMesh::AddVertex(const Vertex& vertex)
    {
        int index = GetNumberOfIndicies();

        m_IndexBuffer.push_back(index);
        m_VertexBuffer.push_back(vertex);
    }

    inline const int* cTextureMesh::GetIndexBuffer() const
    { return (m_IndexBuffer.empty()) ? 0 : &m_IndexBuffer[0]; }

    inline int cTextureMesh::GetIndexByteSize() const
    { return static_cast<int>(sizeof(int)); }

    inline int cTextureMesh::GetNumberOfIndicies() const
    { return static_cast<int>(m_IndexBuffer.size()); }

    inline int cTextureMesh::GetNumberOfVerticies() const
    { return static_cast<int>(m_VertexBuffer.size()); }

    inline const cTextureMesh::Vertex& cTextureMesh::GetVertex(int i) const
    { return m_VertexBuffer[i]; }

    inline const cTextureMesh::Vertex* cTextureMesh::GetVertexBuffer() const
    { return (m_VertexBuffer.empty()) ? 0 : &m_VertexBuffer[0]; }

    inline const int cTextureMesh::GetVertexByteSize() const
    { return static_cast<int>(sizeof(Vertex)); }

} // End namespace GFX

#endif // CTEXTUREMESH_H
