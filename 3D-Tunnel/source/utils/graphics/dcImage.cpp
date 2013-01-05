#include "dcImage.h"
#include <iostream>
#include <SDL_image.h>
#include "helper.h"
using std::cout;
using std::endl;

dcImage::dcImage(const string& file_path)
{
    p_surface_ = IMG_Load(file_path.c_str());
    if(0 == p_surface_) { assert(false); cout << "Error loading image" << file_path << endl; }

    testInvariant();
}

bool dcImage::isTransparent() const
{
    return (0!= p_surface_->format->Amask) || (0!= p_surface_->format->palette);
}

void dcImage::convertPixelFormat()
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
    SDL_SetAlpha(p_surface_, 0, SDL_ALPHA_TRANSPARENT);
    SDL_Surface* p_alpha_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, getWidth(), getHeight(),
                                                        32, rmask, gmask, bmask, amask);
    SDL_BlitSurface(p_surface_, 0, p_alpha_surface, 0);
    p_surface_ = p_alpha_surface;
}
