////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CFace.h
 * \author  Hua Fei Yu 0951402
 * \date    Nov 6, 2011
 * \brief  	Face class, based on face class from OpenGL Obj Loader
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef CFACE_H
#define CFACE_H

#include <boost/array.hpp>

class CFace
{
    public:
        // Methods
                        CFace();
        virtual         ~CFace();
//                void    add(int v, int vn);

        // Members
        boost::array<int,3> v;  //! Vertex indicies
        boost::array<int,3> vn; //! Normal indicies
        boost::array<int,3> vt; //! Texture indicies
};

#endif // CFACE_H
