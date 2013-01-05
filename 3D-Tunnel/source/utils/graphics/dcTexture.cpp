#include "dcTexture.h"
#include "dcImage.h"
#include <gl/glu.h>

void glActiveTexture(GLenum texture);
const GLuint dcTexture::INVALID_ID = ~1;

dcTexture::dcTexture(const string& file_path) :
texture_id_(INVALID_ID),
p_image_(new dcImage(file_path))
{
    is_transparent_ = p_image_->isTransparent();
}

dcTexture::~dcTexture()
{
    //dtor
}

const bool dcTexture::operator==(const dcTexture& rhs) const
{
	return (p_image_ == rhs.p_image_) && (getID() == rhs.getID());
}

void dcTexture::registerGL()
{
    testInvariant();

    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	p_image_->convertPixelFormat();
	const int w = p_image_->getWidth();
	const int h = p_image_->getHeight();

	if (((w&(w-1))==0) && ((h&(h-1))==0))
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_image_->getPixels());
	}
	else
	{
	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, p_image_->getPixels());
	}

	p_image_.reset();
	testInvariant();
}
