#include "helper.h"

#include <limits>


SDL_Surface* load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

GLuint createEmptyTexture(uint x, uint y)
{
    GLuint txtnumber;
    uint* data;

    data = (uint*) new GLuint[((x*y)*4*sizeof(uint)) ];
    ZeroMemory(data,((x*y)*4*sizeof(uint)));

    glGenTextures(1, &txtnumber);       // Create 1D texture
    glBindTexture(GL_TEXTURE_2D, txtnumber);       // Bind texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);    // Build texture using data
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);       // Bind texture
    delete[] data;

    return txtnumber;
}

unsigned int getPixel(SDL_Surface* s, int x, int y)
{
    return ((unsigned int*)s->pixels)[y*(s->pitch/sizeof(unsigned int)) + x];
}

//
//void apply_surface(Vector2D pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
//{
//    //Holds offsets
//    SDL_Rect offset;
//
//    //Get offsets
//    offset.x = pos.intx();
//    offset.y = pos.inty();
//
//    //Blit
//    SDL_BlitSurface( source, clip, destination, &offset );
//}
float FLOAT_MAX()
{
    return std::numeric_limits<float>::max();
}

float min(float a, float b)
{
    return (a > b) ? b : a;
}

float max(float a, float b)
{
    return (a > b) ? a : b;
}

float clamp(float v, float min, float max)
{
    if (v<min) { v=min;}
    else if (v>max) { v=max; }

    return v;
}

inline bool isNAN(float value)				{ return (IR(value)&0x7f800000) == 0x7f800000;	}
inline bool isIndeterminate(float value)	{ return IR(value) == 0xffc00000;				}
inline bool isPlusInf(float value)			{ return IR(value) == 0x7f800000;				}
inline bool isMinusInf(float value)			{ return IR(value) == 0xff800000;				}

inline bool isValidFloat(float value)
{
	if(isNAN(value))			return false;
	if(isIndeterminate(value))	return false;
	if(isPlusInf(value))		return false;
	if(isMinusInf(value))		return false;
	return true;
}

//int max(int i, int b)
//{
//    if (i > b)
//        return i;
//    return b;
//}
//double max(double i, double b)
//{
//    if (i > b)
//        return i;
//    return b;
//}
//SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
//{
//  // 'display' is the surface whose format you want to match
//  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode
//
//  const SDL_PixelFormat& fmt = *(display->format);
//  return SDL_CreateRGBSurface(flags,width,height,
//                  fmt.BitsPerPixel,
//                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
//}

float sign(float v)
{
    return (v > 0.0f)  ? 1.0f : -1.0f;
}

