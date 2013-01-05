#define GL_GLEXT_PROTOTYPES // Need this first

#include "graphics/dcVBO.h"

#include "gl/glext.h"

// function pointers for VBO Extension
// Windows needs to get function pointers from ICD OpenGL drivers,
// because opengl32.dll does not support extensions higher than v1.1.

    #ifdef _WIN32
        PFNGLGENBUFFERSARBPROC pglGenBuffersARB = 0;                     // VBO Name Generation Procedure
        PFNGLBINDBUFFERARBPROC pglBindBufferARB = 0;                     // VBO Bind Procedure
        PFNGLBUFFERDATAARBPROC pglBufferDataARB = 0;                     // VBO Data Loading Procedure
        PFNGLBUFFERSUBDATAARBPROC pglBufferSubDataARB = 0;               // VBO Sub Data Loading Procedure
        PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB = 0;               // VBO Deletion Procedure
        PFNGLGETBUFFERPARAMETERIVARBPROC pglGetBufferParameterivARB = 0; // return various parameters of VBO
        PFNGLMAPBUFFERARBPROC pglMapBufferARB = 0;                       // map VBO procedure
        PFNGLUNMAPBUFFERARBPROC pglUnmapBufferARB = 0;                   // unmap VBO procedure
        #define glGenBuffersARB           pglGenBuffersARB
        #define glBindBufferARB           pglBindBufferARB
        #define glBufferDataARB           pglBufferDataARB
        #define glBufferSubDataARB        pglBufferSubDataARB
        #define glDeleteBuffersARB        pglDeleteBuffersARB
        #define glGetBufferParameterivARB pglGetBufferParameterivARB
        #define glMapBufferARB            pglMapBufferARB
        #define glUnmapBufferARB          pglUnmapBufferARB
    #endif

bool dcVBO::initialized_ = false;
void dcVBO::init()
{
    if (initialized_) { return; }
    #ifdef _WIN32
        // get pointers to GL functions
        glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
        glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
        glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
        glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)wglGetProcAddress("glBufferSubDataARB");
        glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
        glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)wglGetProcAddress("glGetBufferParameterivARB");
        glMapBufferARB = (PFNGLMAPBUFFERARBPROC)wglGetProcAddress("glMapBufferARB");
        glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)wglGetProcAddress("glUnmapBufferARB");
    #endif
    initialized_ = true;
}

void dcVBO::DeleteBuffersARB(int size, const GLuint* buffers)
{
    glDeleteBuffersARB(size, buffers);
}

void dcVBO::GenBuffersARB(int size, GLuint* buffers)
{
    glGenBuffersARB(size, buffers);
}

void dcVBO::BindBufferARB(GLenum target, GLuint buffer)
{
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer);
}

void dcVBO::BufferDataARB(GLenum target, GLintptr offset, GLvoid* data, GLenum usage)
{
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, offset, data, usage);
}

void dcVBO::BufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid* data)
{
    glBufferSubDataARB(target, offset, size, data);
}
