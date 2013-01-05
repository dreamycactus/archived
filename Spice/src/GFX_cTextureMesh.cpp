/**
 * cTextureMesh based somewhat on globjview on dhpoware
 */

#define GL_GLEXT_PROTOTYPES // Need for VBO

#include <SDL2/SDL_opengl.h>
#include "GFX_cTextureMesh.hpp"


using namespace GFX;

cTextureMesh::cTextureMesh(bool useVbo)
{
    Initialise(100, useVbo);
}

cTextureMesh::cTextureMesh(int initial_sz, bool useVbo)
{
    Initialise(initial_sz, useVbo);
}

cTextureMesh::~cTextureMesh()
{
    Destroy();
}

void cTextureMesh::Initialise(int initial_sz, bool useVbo)
{
    m_VertexBuffer.reserve(100);
    m_IndexBuffer.reserve(100);
    m_UseVbo = useVbo;
    m_VboId = 0;
    m_nBufferSize = 0;
}

void cTextureMesh::Destroy()
{
    m_VertexBuffer.clear();
    m_IndexBuffer.clear();
}

void cTextureMesh::GenerateVbo()
{
//    glGenBuffersARB(1, &m_VboId);
//    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VboId);
//    glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vertex)*m_VertexBuffer.size(), 0, GL_STREAM_DRAW_ARB);
//    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(Vertex)*m_VertexBuffer.size(), GetVertexBuffer());
//    glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &m_nBufferSize);
}

void cTextureMesh::Render()
{
//    if (m_UseVbo) {
//
////    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VboId);         // for vertex coordinates
//    }

    // Enable client states and add array data

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, GetVertexByteSize(), GetVertexBuffer()->pos);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, GetVertexByteSize(),GetVertexBuffer()->tex_coord);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, GetVertexByteSize(),GetVertexBuffer()->col);

    // Draw
    glDrawArrays(GL_QUADS, 0, GetNumberOfIndicies());
    //glDrawElements(GL_QUADS, GetNumberOfIndicies(), GL_UNSIGNED_INT, GetIndexBuffer());

    // Disable client states
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

//    if (m_UseVbo) {
//        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);         // for vertex coordinates
//    }
}
