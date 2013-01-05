// Headers
#include "graphics/shapes.h"
#include "graphics/dcVBO.h"
#include <math.h>
#include <cassert>


#include <iostream>
void DrawLine(const Vec2f& p1, const Vec2f& p2, const Vec3f& c1, const Vec3f& c2)
{
    glBegin(GL_LINES);
        glColor3f(c1.x, c1.y, c1.z);
        glVertex2f(p1.x, p1.y);
        glColor3f(c2.x, c2.y, c2.z);
        glVertex2f(p2.x, p2.y);
    glEnd();
}

void DrawQuad(const Vec2f& p1, const Vec2f& p2, const Vec2f& p3,
              const Vec2f& p4, const Vec3f& c=Vec3f(0.f, 1.f, 1.f))
{
    glBegin(GL_QUADS);
        glColor3f(c.x, c.y, c.z);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
    glEnd();
}

void DrawRectangle(const Vec2f& p1, const Vec2f& p2)
{
    Vec2f delta = p2-p1;
    DrawQuad(p1, Vec2f(p1.x, p1.y+delta.y), p2, Vec2f(p1.x+delta.x, p1.y));
}

void DrawCircle(const Vec2f& p, float r, float step)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(p.x, p.y);
        for (float i=0.f; i<2.f*pi+step; i=i+step)
        {
            glVertex2f(p.x + sin(i) * r, p.y + cos(i) * r);
        }

    glEnd();
}

void getCylinderVerticies(uint circle_slices, uint lengthwise_slices, float radius, float slice_length, const Vec3f& offset, const dcColour& colour, GLuint& id)
{
    uint vertex_count           = circle_slices * lengthwise_slices * 4; // Same as normal offset
    uint num_vertexplusnormal   = vertex_count * 2; // * 4 for each vertex in quad. * 3 for vertex, normal colour
    uint normal_offset          = vertex_count;


    Vec3f*    vertex_array = new Vec3f[num_vertexplusnormal];
    dcColour* colour_array = new dcColour[vertex_count+4];

    float degree_slice  = 360.0f/(float)circle_slices;
    float degree_left, degree_right;
    Vec3f v1, v2, n;            // For calculating normals
    dcColour col = colour;

    for (uint i=0; i<lengthwise_slices; ++i)
    {
        col.r -= 0.01f;
        col.g -= 0.01f;
        col.b -= 0.01f;
        for (uint j=0; j<circle_slices; ++j)
        {
                // Verticies
                degree_left  = dcMath::degreesToRadians((j+1)*degree_slice);      // Calculate degree based on slice left corner of quad
                degree_right = dcMath::degreesToRadians((j+0)*degree_slice);      // Calculate degree based on slice right

                vertex_array[(i*circle_slices+j)*4+0] = Vec3f(radius * cos(degree_right),  radius * sin(degree_right),  -(float)(i+0)*slice_length) + offset;   // Vertex coord
                vertex_array[(i*circle_slices+j)*4+1] = Vec3f(radius * cos(degree_left), radius * sin(degree_left),     -(float)(i+0)*slice_length) + offset;   // Vertex coord
                vertex_array[(i*circle_slices+j)*4+2] = Vec3f(radius * cos(degree_left), radius * sin(degree_left),     -(float)(i+1)*slice_length) + offset;   // Vertex coord
                vertex_array[(i*circle_slices+j)*4+3] = Vec3f(radius * cos(degree_right),  radius * sin(degree_right),  -(float)(i+1)*slice_length) + offset;   // Vertex coord

                // Normals
                v1 = vertex_array[(i*circle_slices+j)*4+1]-vertex_array[(i*circle_slices+j)*4+0];   // v2 - v1
                v2 = vertex_array[(i*circle_slices+j)*4+2]-vertex_array[(i*circle_slices+j)*4+0];   // v3 - v2
                n = v1^v2;
                n.normalize();
//                n = -n;
                vertex_array[(i*circle_slices+j)*4+0+normal_offset] = n;
                vertex_array[(i*circle_slices+j)*4+1+normal_offset] = n;
                vertex_array[(i*circle_slices+j)*4+2+normal_offset] = n;
                vertex_array[(i*circle_slices+j)*4+3+normal_offset] = n;

                // Colours
                colour_array[(i*circle_slices+j)*4+0] = col;
                colour_array[(i*circle_slices+j)*4+1] = col;
                colour_array[(i*circle_slices+j)*4+2] = col;
                colour_array[(i*circle_slices+j)*4+3] = col;
        }
    }
//    vertex_array[vertex_count+0] = Vec3f(-radius, -radius, lengthwise_slices*slice_length);
//    vertex_array[vertex_count+1] = Vec3f(radius, -radius, lengthwise_slices*slice_length);
//    vertex_array[vertex_count+2] = Vec3f(radius, radius, lengthwise_slices*slice_length);
//    vertex_array[vertex_count+3] = Vec3f(-radius, radius, lengthwise_slices*slice_length);
//
//    vertex_array[vertex_count+normal_offset+0] = Vec3f(0.0f,0.0f,-1.0f);
//    vertex_array[vertex_count+normal_offset+1] = Vec3f(0.0f,0.0f,-1.0f);
//    vertex_array[vertex_count+normal_offset+2] = Vec3f(0.0f,0.0f,-1.0f);
//    vertex_array[vertex_count+normal_offset+3] = Vec3f(0.0f,0.0f,-1.0f);
//
//    colour_array[vertex_count+0] = colour;
//    colour_array[vertex_count+1] = colour;
//    colour_array[vertex_count+2] = colour;
//    colour_array[vertex_count+3] = colour;


    std::cout << sizeof(Vec3f)*(num_vertexplusnormal)+sizeof(dcColour)*(vertex_count);
    dcVBO::GenBuffersARB(1, &id);
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER, id);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*(num_vertexplusnormal)+sizeof(dcColour)*(vertex_count), 0, GL_STATIC_DRAW);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(Vec3f)*(num_vertexplusnormal), vertex_array);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*(num_vertexplusnormal), sizeof(dcColour)*(vertex_count), colour_array);

    delete vertex_array;
    delete colour_array;
}

void renderArrow(const Vec2f& p1, const Vec2f& p2)
{
    Vec2f delta = p2-p1;
    delta.norm();
    delta *= 10;

    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p2.x-delta.x-delta.y, p2.y-delta.y+delta.x);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p2.x-delta.x+delta.y, p2.y-delta.y-delta.x);
    glEnd();
}



// Code adapted from http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
void renderSphere(float r, int lats, int longs)
{
	int i, j;

	for(i = 0; i <= lats; i++)
	{
		  float lat0 = M_PI * (-0.5 + (float) (i - 1) / lats);
		  float z0  = sin(lat0)*r;
		  float zr0 =  cos(lat0);

		  float lat1 = M_PI * (-0.5 + (float) i / lats);
		  float z1 = sin(lat1)*r;
		  float zr1 = cos(lat1);

		  glBegin(GL_QUAD_STRIP);
			  for(j = 0; j <= longs; j++)
			  {
				  float lng = 2 * M_PI * (float) (j - 1) / longs;
				  float x = cos(lng)*r;
				  float y = sin(lng)*r;

				  glNormal3f(x * zr0, y * zr0, z0);
				  glVertex3f(x * zr0, y * zr0, z0);
				  glNormal3f(x * zr1, y * zr1, z1);
				  glVertex3f(x * zr1, y * zr1, z1);
			  }
		  glEnd();
	}
}

void drawAxis()
{
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0,0,0);
		glVertex3f(50,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,50,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,50);
	glEnd();
}

//void solidSphere(GLdouble radius, GLint slices, GLint stacks)
//{
//	glColor3f(1, 0, 0);
//	glBegin(GL_LINE_LOOP);
//		GLUquadricObj* quadric = gluNewQuadric();
//
//		gluQuadricDrawStyle(quadric, GLU_FILL);
//		gluSphere(quadric, radius, slices, stacks);
//		gluDeleteQuadric(quadric);
//	glEnd();
//
//
//
//}
