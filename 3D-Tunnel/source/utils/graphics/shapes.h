////////////////////////////////////////////////////////////////////////////////
/**
 * \file    shapes.h
 * \author  Hua Fei Yu 0951402
 * \date    September 20, 2011.
 * \brief   Contains function prototypes for drawing primitives
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

// Headers
#include "SDL/SDL_opengl.h"
#include "dcMath.h"
#include "mytypes.h"


// 2D
void DrawLine(const Vec2f& p1, const Vec2f& p2, const Vec3f& c1, const Vec3f& c2);

void DrawQuad(const Vec2f& p1, const Vec2f& p2, const Vec2f& p3,
              const Vec2f& p4, const Vec3f& c);

void DrawRectangle(const Vec2f& p1, const Vec2f& p2);

void DrawCircle(const Vec2f& p, float r, float step=0.2f);

void getCylinderVerticies(uint circle_slices, uint lengthwise_slices, float radius, float slice_length, const Vec3f& offset, const dcColour& colour, GLuint& id);

void renderArrow(const Vec2f& p1, const Vec2f& p2);


// 3D
void renderSphere(float r, int lats, int longs);

void drawAxis();


#endif // SHAPES_H_INCLUDED
