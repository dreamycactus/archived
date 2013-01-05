#ifndef CMESH_H
#define CMESH_H
#include "gl/gl.h"
#include "graphics/dcVBO.h"
#include "tokens/CMaterial.h"
#include "graphics/dcTexture.h"
#include <vector>
#include "tokens/cFace.h"
using std::vector;

class Vec3f;
class Vec2f;

class CMesh
{
    public:
    // Functions
                        CMesh();
        virtual         ~CMesh();

        void            generateFlatNormals();
        void            generateSmoothNormals();

        void            setVBO(GLuint id);
        void            setArrays(Vec3f* vbuffer, GLuint vbsz, Vec3f* nbuffer,
                                  GLuint nbsz, Vec2f* tbuffer, GLuint tbsz);
        void            generate();

        void            render();

        void            setMaterial(const CMaterial& mtl) { material_ = mtl; }
        void            setTexture(const shared_ptr<dcTexture>& rhs) { texture_ = rhs; }


        const bool      hasNormals() const      { return false; }
        const bool      hasTextureCoords() const { return has_texture_; } // Does nothing for now.
        void            setHasTexture(bool b) {has_texture_ = b;}
//        const int       getVertexCount() const  { return (verticies_.size() > 0); }
//        const int       getNormalCount() const  { return (normals_.size() > 0); }
//        const int       getFaceCount() const    { return (faces_.size() > 0); }
        void            activateColourMaterial() { colour_mat_ = true; }
    protected:
        GLuint buffer_ids_[3];      //!< VBO objects [0] is vertex, [1] is normals

        Vec3f* vertex_buffer_;
        Vec3f* normal_buffer_;
        Vec2f* texture_buffer_;

        GLuint vertex_buffer_sz_;
        GLuint normal_buffer_sz_;
        GLuint texture_buffer_sz_;

        shared_ptr<dcTexture> texture_;
        CMaterial material_;

        bool has_texture_;
        bool colour_mat_;

};

#endif // CMESH_H
