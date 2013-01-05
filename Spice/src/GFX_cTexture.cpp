/**
 *
 */

#include "GFX_cTexture.hpp"
#include "GFX_cImage.hpp"
#include <GL/glu.h>

#include <iostream>

using namespace GFX;

cTexture::~cTexture()
{}

//
cTexture::cTexture(const string& str_filepath)
: cTextureWrapper()
, m_pImage(new cImage(str_filepath))
{
	m_is_transparent = m_pImage->IsTransparent();
    SetTextureWidth(m_pImage->GetWidth());
	SetTextureHeight(m_pImage->GetHeight());
}

//
const bool cTexture::operator==(const cTexture& rhs) const
{
	return (m_pImage.get() == rhs.m_pImage.get()) && (GetID() == rhs.GetID());
}

//
void cTexture::RegisterGL()
{
	glGenTextures (1, &m_TextureID);

//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);

	glBindTexture (GL_TEXTURE_2D, m_TextureID);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST and GL_NEAREST -> no filter -> Crisp
//	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_pImage->ConvertPixelFormat();

	SetBytesPerPixel(m_pImage->GetBytesPerPixel());
	SetTextureFormat(m_pImage->GetTextureFormat());

	int width = GetTextureWidth();
	int height = GetTextureHeight();



	if (((width & (width-1)) == 0) && ((height & (height-1)) == 0))
		glTexImage2D(GL_TEXTURE_2D, 0, m_pImage->GetBytesPerPixel(), width, height, 0, m_pImage->GetTextureFormat(), GL_UNSIGNED_BYTE, m_pImage->GetPixels());
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, m_pImage->GetBytesPerPixel(), width, height, m_pImage->GetTextureFormat(), GL_UNSIGNED_BYTE, m_pImage->GetPixels());

    CheckTexture();

//	m_pImage.reset();


}
