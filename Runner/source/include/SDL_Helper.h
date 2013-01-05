#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <string>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "CSoundEffect.h"
#include "Vector2D.h"





SDL_Surface *load_image( std::string filename );
void apply_surface( Vector2D pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
int max(int i, int b);
int RandInt(int min, int max);
double RandDouble(double min, double max);
SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display);
#endif //SDL_HELPER
