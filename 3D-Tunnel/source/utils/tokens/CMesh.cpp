#include "tokens/CMesh.h"
#include "dcMath.h"
#include "mytypes.h"
#include "graphics/dcVBO.h"

#include <iostream>
using namespace std;


CMesh::CMesh()
{
    // Chrome
    material_.ka = { 0.25f,0.25f,0.25f };
    material_.kd = { 0.4f,0.4f,0.4f };
    material_.ks = { 0.774597f,0.774597f,0.774597f };
    material_.ns = 0.6f;
    has_texture_ = true;

}

CMesh::~CMesh()
{

    delete[] vertex_buffer_;
    delete[] normal_buffer_;
    delete[] texture_buffer_;
    vertex_buffer_ = 0;
    normal_buffer_ = 0;
    texture_buffer_ = 0;
    dcVBO::DeleteBuffersARB(3, &buffer_ids_[0]);
}

void CMesh::generateFlatNormals()
{
    for (uint i=0; i<normal_buffer_sz_/3; ++i)
    {
        const Vec3f& v1 = vertex_buffer_[i*3+0];
        const Vec3f& v2 = vertex_buffer_[i*3+1];
        const Vec3f& v3 = vertex_buffer_[i*3+2];
        Vec3f v = v2-v1;
        Vec3f w = v3-v1;
        Vec3f vn = (v^w);

        vn.normalize();
        normal_buffer_[i*3+0] = vn;
        normal_buffer_[i*3+1] = vn;
        normal_buffer_[i*3+2] = vn;
    }
}



void CMesh::render()
{
    if (!colour_mat_)
    {
        glDisable(GL_COLOR_MATERIAL);

        material_.ks = { 1.0f, 0.0f, 0.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_.ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_.kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_.ks);
        glMaterialf(GL_FRONT, GL_SHININESS, material_.ns);
    }
    else
    { glEnable(GL_COLOR_MATERIAL); }


    if (has_texture_)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_->getID());
    }


//     Enable array mode
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, buffer_ids_[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, buffer_ids_[1]);
    glNormalPointer(GL_FLOAT, 0, 0);

    if (has_texture_)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        dcVBO::BindBufferARB(GL_ARRAY_BUFFER, buffer_ids_[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
    }
    // Draw vbos
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_sz_);

    // Disable array mode
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    if (has_texture_)
    { glDisableClientState(GL_TEXTURE_COORD_ARRAY); }

    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

    glDisable(GL_TEXTURE_2D);

}

void CMesh::setVBO(GLuint id)
{
}

void CMesh::setArrays(Vec3f* vbuffer, GLuint vbsz, Vec3f* nbuffer, GLuint nbsz,
                       Vec2f* tbuffer, GLuint tbsz)
{
    vertex_buffer_      = vbuffer;
    vertex_buffer_sz_   = vbsz;
    normal_buffer_      = nbuffer;
    normal_buffer_sz_   = nbsz;
    texture_buffer_     = tbuffer;
    texture_buffer_sz_  = tbsz;

}
#include <iostream>
void CMesh::generate()
{
    generateFlatNormals();
    // Generate buffers
    dcVBO::GenBuffersARB(3, &buffer_ids_[0]);

    // Set Vertex Data
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER, buffer_ids_[0]);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*(vertex_buffer_sz_), vertex_buffer_, GL_STREAM_DRAW_ARB);
//    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(Vec3f)*(vertex_buffer_sz_), vertex_buffer_);

    // Set Normal Data
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER, buffer_ids_[1]);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*(normal_buffer_sz_), normal_buffer_, GL_STREAM_DRAW_ARB);
//    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(Vec3f)*normal_buffer_sz_, normal_buffer_);

    if (has_texture_)
    {
    // Set Texture Data
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER, buffer_ids_[2]);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER, sizeof(Vec2f)*(texture_buffer_sz_), texture_buffer_, GL_STREAM_DRAW_ARB);
//    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(Vec2f)*(texture_buffer_sz_), texture_buffer_);
    }

}
