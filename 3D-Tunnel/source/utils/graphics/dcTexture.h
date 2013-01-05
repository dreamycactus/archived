#ifndef DCTEXTURE_H
#define DCTEXTURE_H

#include <gl/gl.h>
#include <boost/shared_ptr.hpp>
#include <cassert>
#include "dcImage.h"
class dcImage;

using boost::shared_ptr;
class dcTexture
{
    public:
                        dcTexture(){}
                        dcTexture(const string& file_path);
        virtual         ~dcTexture();

        const bool      operator==(const dcTexture& rhs) const;

        const           GLuint getID() const     { return texture_id_; }
        const bool      isTransparent() const    { return is_transparent_; }
        const bool      isRegistered() const     { return 0 == p_image_; }
        void            registerGL();
        inline void     testInvariant() const    { assert(NULL != p_image_ || INVALID_ID != texture_id_);}

        static const GLuint INVALID_ID;
    private:
        GLuint texture_id_;
        bool is_transparent_;
        shared_ptr<dcImage> p_image_;
};

#endif // DCTEXTURE_H
