////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CMaterial.h
 * \author  Hua Fei Yu 0951402
 * \date    Nov 6, 2011
 * \brief  	Triangle Mesh class, based on mesh class from OpenGL Obj Loader
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef CMATERIAL_H
#define CMATERIAL_H

// Headers
#include "SDL/SDL_opengl.h"

class CMaterial
{
    public:
    // Methods
        CMaterial() {}
        virtual ~CMaterial() {}

    // Members
        GLfloat ns;     //! Shininess
        GLfloat ka[4];  //! Ambient
        GLfloat kd[4];  //! Diffuse
        GLfloat ks[4];  //! Specular
    protected:
};

#endif // CMATERIAL_H
