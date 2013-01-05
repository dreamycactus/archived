#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <time.h>
#include "SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL_image.h"
#include "mytypes.h"

#define IR(x)					((uint&)(x))


float FLOAT_MAX();

SDL_Surface* load_image( std::string filename ); // From lazy foo's tutorial
//void apply_surface( Vector2D pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
//int max(int i, int b);

// http://old.nabble.com/Getting-pixel-color-value-at-%28x,y%29-from-an-SDL_Surface-----td19443874.html
unsigned int getPixel(SDL_Surface* s, int x, int y);

float min(float a, float b);
float max(float a, float b);
float clamp(float v, float min, float max);
float sign(float v);

bool isValidFloat(float f);
//SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display);

GLuint createEmptyTexture(uint x, uint y);

#endif //HELPER
