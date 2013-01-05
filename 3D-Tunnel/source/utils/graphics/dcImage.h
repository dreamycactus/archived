#ifndef DCIMAGE_H
#define DCIMAGE_H

#include <string>
#include <gl/gl.h>
#include <SDL/SDL.h>
#include <cassert>
using std::string;
class dcImage
{
    public:
        dcImage(const string& file_path);
        virtual ~dcImage() { SDL_FreeSurface(p_surface_); p_surface_ = 0; }

        bool isTransparent() const;
        void convertPixelFormat();
        const GLint getWidth() const    { testInvariant(); return p_surface_->w; }
        const GLint getHeight() const   { testInvariant(); return p_surface_->h; }
        const void* getPixels() const   { testInvariant(); return p_surface_->pixels; }

        inline void testInvariant() const { assert(p_surface_ != 0); }
    private:
        dcImage(const dcImage& rhs);            // Don't implement
        dcImage& operator=(const dcImage& rhs); // Don't implement

        SDL_Surface* p_surface_;
};

#endif // DCIMAGE_H
