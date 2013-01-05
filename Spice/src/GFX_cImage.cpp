#include "GFX_cImage.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

using namespace GFX;
using std::cout;
using std::endl;

cImage::cImage(const string& str_filepath)
: m_pSurface(0)
, m_nColors(0)
, m_TextureFormat(0)
{
	//	load the image file
	m_pSurface = IMG_Load(str_filepath.c_str());
	if (m_pSurface==0) {
	    //throw cImageLoadException(SDL_GetError());
	    cout << "Could not load: " << str_filepath << endl;
	}
	CheckImage();

	m_nColors = m_pSurface->format->BytesPerPixel;
}

const unsigned int cImage::GetPixel(int x, int y) const //actually no need to convert to hex color after this
{
    //bam, word-for-word http://www.libsdl.org/cgi/docwiki.cgi/Pixel_Access
    int bpp = m_pSurface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)m_pSurface->pixels + y * m_pSurface ->pitch + x * bpp; //watch out! sometimes this is 8, 16, 24, 32 not 1, 2, 3, 4 (divide by 8!)

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       // shouldn't happen, but avoids warnings
    }
}

bool cImage::IsTransparent() const
{
    Uint32 key = 0;
	return (m_pSurface->format->Amask != 0) || (SDL_GetColorKey(m_pSurface, &key) != -1);
}

void cImage::ConvertPixelFormat()
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

    if (m_nColors == 4) {
        if (m_pSurface->format->Rmask == 0x000000ff)
            m_TextureFormat = GL_RGBA;
        else
            m_TextureFormat = GL_BGRA;
    } else if (m_nColors == 3) {
        if (m_pSurface->format->Rmask == 0x000000ff)
            m_TextureFormat = GL_RGB;
        else
            m_TextureFormat = GL_BGR;
    } else {
            printf("warning: the image is not truecolor..  this will probably break\n");
            // this error should not go unhandled
    }
//    SDL_Color color;
//    SDL_GetRGB(*(Uint32 *)m_pSurface->pixels, m_pSurface->format, &color.r, &color.g, &color.b);
//	SDL_Surface* p_alpham_pSurface = SDL_CreateRGBSurface(0, GetWidth(), GetHeight(),
//													  32, rmask, gmask, bmask, amask);
//	SDL_BlitSurface(m_pSurface, 0, p_alpham_pSurface, 0);
//	SDL_FreeSurface(m_pSurface);
//	m_pSurface = p_alpham_pSurface;


}
