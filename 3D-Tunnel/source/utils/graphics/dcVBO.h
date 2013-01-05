#ifndef DCVBO_H
#define DCVBO_H

//#define GL_GLEXT_PROTOTYPES // Need this first

//#include "gl/glext.h"
#include "gl/gl.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"



class dcVBO
{
    public:
    static void init();

    static void DeleteBuffersARB(int size, const GLuint* buffers);
    static void GenBuffersARB(int size, GLuint* buffers);
    static void BindBufferARB(GLenum target, GLuint buffer);
    static void BufferDataARB(GLenum target, GLintptr offset, GLvoid* data, GLenum usage);
    static void BufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid* data);
    private:
    static bool initialized_;
};

#endif // DCVBO_H
