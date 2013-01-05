////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Contains a pair class and the includes to the SAP procedure
 *  \file       mytypes.h
 *  \author     Hua Fei Yu
 *  \date       July 13, 2011
 *  \brief		Basically Pierre Terdiman's work, reformatted!
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef MYTYPES_H
#define MYTYPES_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// typedefs & defines
#define IEEE_1_0				0x3f800000					//!< integer representation of 1.0
#define IEEE_255_0				0x437f0000					//!< integer representation of 255.0
#define IEEE_MAX_FLOAT			0x7f7fffff					//!< integer representation of MAX_FLOAT
#define IEEE_MIN_FLOAT			0xff7fffff					//!< integer representation of MIN_FLOAT


    typedef unsigned int		uint;       //!< sizeof(uword)	must be 2
    typedef int	                BOOL;       //!< Another boolean type
    typedef unsigned char		ubyte;		//!< sizeof(ubyte)	must be 1

    struct TPair
    {
        inline          TPair()                                       {}
        inline          TPair(uint i0, uint i1) : id0(i0), id1(i1)    {}

        uint   id0;    //!< First index of pair
        uint   id1;    //!< Second index of pair
    };

    struct dcColour
    {
        inline dcColour() {}
        inline dcColour(float r1, float g1, float b1, float a1)
        {
            r = r1;
            g = g1;
            b = b1;
            a = a1;
        }
        float r, g, b, a;
    };



    #ifndef FALSE
    #define FALSE               0
    #endif

    #ifndef TRUE
    #define TRUE                1
    #endif

    struct TAxes
    {
        uint Axis0; // X axis
        uint Axis1; // Y axis
    };




#endif //MYTYPES_H
