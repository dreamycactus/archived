#include "../include/SDL_Helper.h"


SDL_Surface *load_image( std::string filename )
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

void apply_surface(Vector2D pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = pos.intx();
    offset.y = pos.inty();

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

int RandInt(int min, int max)
{
    return rand() % (max-min+1) + min;
}

double RandDouble(double min, double max)
{
    return min + ((max-min) * rand()) / (RAND_MAX + 1.0);
}

int max(int i, int b)
{
    if (i > b)
        return i;
    return b;
}
double max(double i, double b)
{
    if (i > b)
        return i;
    return b;
}
SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}



