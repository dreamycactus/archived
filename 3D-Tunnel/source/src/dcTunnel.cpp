#include "dcTunnel.h"
#include "graphics/dcVBO.h"
#include "graphics/shapes.h"
#include "tokens/CMaterial.h"
#define BUFFER_OFFSET(i) ((char*)NULL + (i))
#include <iostream>
using namespace std;

dcTunnel::dcTunnel()
{
    built_ = false;
    colour_array_ = 0;
    vbo_id_ =0;
}

dcTunnel::~dcTunnel()
{
    if (vbo_id_){dcVBO::DeleteBuffersARB(1, &vbo_id_);}

    if (colour_array_) {delete colour_array_; }
    colour_array_ = 0;
}

dcTunnel::dcTunnel(uint c_slice, uint l_slice, float radius, float seg_len)
{
    init(c_slice, l_slice, radius, seg_len);
}

void dcTunnel::init(uint c_slice, uint l_slice, float radius, float seg_len)
{
    CIRCLE_SLICES       = c_slice;
    LENGTHWISE_SLICES   = l_slice;
    RADIUS              = radius;
    SEGMENT_LENGTH      = seg_len;
    VERTEX_COUNT        = CIRCLE_SLICES *LENGTHWISE_SLICES * 4;
    base_colour_        = dcColour(0.2f, 0.2f, 0.2f, 1.0f);
    colour_decay_       = 0.6f;
    if (!built_)        { buildTunnel(); }
}
void dcTunnel::buildTunnel()
{
    normal_offset_         = CIRCLE_SLICES * LENGTHWISE_SLICES * 4;
    colour_offset_         = CIRCLE_SLICES * LENGTHWISE_SLICES * 4 * 2;

    uint vertex_count           = CIRCLE_SLICES * LENGTHWISE_SLICES * 4; // Same as normal offset
    uint num_vertexplusnormal   = vertex_count * 2; // * 4 for each vertex in quad. * 3 for vertex, normal colour
    colour_array_sz_            = vertex_count;

    Vec3f*    vertex_array = new Vec3f[num_vertexplusnormal];
    colour_array_ = new dcColour[colour_array_sz_];              // Need this array later..

    float degree_slice  = 360.0f/(float)CIRCLE_SLICES;
    float degree_left, degree_right;
    Vec3f v1, v2, n;            // For calculating normals
    dcColour col = base_colour_;

    for (uint i=0; i<LENGTHWISE_SLICES; ++i)
    {
        col.r = base_colour_.r - (base_colour_.r*i/LENGTHWISE_SLICES)*colour_decay_;
        col.g = base_colour_.g - (base_colour_.g*i/LENGTHWISE_SLICES)*colour_decay_;
        col.b = base_colour_.b - (base_colour_.b*i/LENGTHWISE_SLICES)*colour_decay_;
        for (uint j=0; j<CIRCLE_SLICES; ++j)
        {
                // Verticies
                degree_left  = dcMath::degreesToRadians((j+1)*degree_slice);      // Calculate degree based on slice left corner of quad
                degree_right = dcMath::degreesToRadians((j+0)*degree_slice);      // Calculate degree based on slice right

                vertex_array[(i*CIRCLE_SLICES+j)*4+0] = Vec3f(RADIUS * cos(degree_right),  RADIUS * sin(degree_right),  -(float)(i+0)*SEGMENT_LENGTH);   // Vertex coord
                vertex_array[(i*CIRCLE_SLICES+j)*4+1] = Vec3f(RADIUS * cos(degree_left), RADIUS * sin(degree_left),     -(float)(i+0)*SEGMENT_LENGTH);   // Vertex coord
                vertex_array[(i*CIRCLE_SLICES+j)*4+2] = Vec3f(RADIUS * cos(degree_left), RADIUS * sin(degree_left),     -(float)(i+1)*SEGMENT_LENGTH);   // Vertex coord
                vertex_array[(i*CIRCLE_SLICES+j)*4+3] = Vec3f(RADIUS * cos(degree_right),  RADIUS * sin(degree_right),  -(float)(i+1)*SEGMENT_LENGTH);   // Vertex coord

                // Normals
                v1 = vertex_array[(i*CIRCLE_SLICES+j)*4+1]-vertex_array[(i*CIRCLE_SLICES+j)*4+0];   // v2 - v1
                v2 = vertex_array[(i*CIRCLE_SLICES+j)*4+2]-vertex_array[(i*CIRCLE_SLICES+j)*4+0];   // v3 - v2
                n = v1^v2;
                n.normalize();
//                n = -n;
                vertex_array[(i*CIRCLE_SLICES+j)*4+0+normal_offset_] = n;
                vertex_array[(i*CIRCLE_SLICES+j)*4+1+normal_offset_] = n;
                vertex_array[(i*CIRCLE_SLICES+j)*4+2+normal_offset_] = n;
                vertex_array[(i*CIRCLE_SLICES+j)*4+3+normal_offset_] = n;

                // Colours
                colour_array_[(i*CIRCLE_SLICES+j)*4+0] = col;
                colour_array_[(i*CIRCLE_SLICES+j)*4+1] = col;
                colour_array_[(i*CIRCLE_SLICES+j)*4+2] = col;
                colour_array_[(i*CIRCLE_SLICES+j)*4+3] = col;
        }
    }
//    vertex_array[vertex_count+0] = Vec3f(-RADIUS, -RADIUS, LENGTHWISE_SLICES*SEGMENT_LENGTH);
//    vertex_array[vertex_count+1] = Vec3f(RADIUS, -RADIUS, LENGTHWISE_SLICES*SEGMENT_LENGTH);
//    vertex_array[vertex_count+2] = Vec3f(RADIUS, RADIUS, LENGTHWISE_SLICES*SEGMENT_LENGTH);
//    vertex_array[vertex_count+3] = Vec3f(-RADIUS, RADIUS, LENGTHWISE_SLICES*SEGMENT_LENGTH);
//
//    vertex_array[vertex_count+normal_offset+0] = Vec3f(0.0f,0.0f,-1.0f);
//    vertex_array[vertex_count+normal_offset+1] = Vec3f(0.0f,0.0f,-1.0f);
//    vertex_array[vertex_count+normal_offset+2] = Vec3f(0.0f,0.0f,-1.0f);
//    vertex_array[vertex_count+normal_offset+3] = Vec3f(0.0f,0.0f,-1.0f);
//
//    colour_array_[vertex_count+0] = colour;
//    colour_array_[vertex_count+1] = colour;
//    colour_array_[vertex_count+2] = colour;
//    colour_array_[vertex_count+3] = colour;


    std::cout << sizeof(Vec3f)*(num_vertexplusnormal)+sizeof(dcColour)*(vertex_count);
    dcVBO::GenBuffersARB(1, &vbo_id_);
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER, vbo_id_);
    dcVBO::BufferDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*(num_vertexplusnormal)+sizeof(dcColour)*(vertex_count), 0, GL_STREAM_DRAW);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(Vec3f)*(num_vertexplusnormal), vertex_array);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*(num_vertexplusnormal), sizeof(dcColour)*(vertex_count), colour_array_);

    delete vertex_array;
    built_ = true;
}

void dcTunnel::render()
{

    material_.ka = { 0.02,0.02,0.02f };
    material_.kd = { 0.01f,0.01f,0.01f };
    material_.kd = { 0.4f,0.4f,0.4f };
    material_.ns = 10.0f;

//    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_.ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_.kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_.ks);
	glMaterialf(GL_FRONT, GL_SHININESS, material_.ns);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    dcVBO::BindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_);

    glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET(sizeof(Vec3f)*normal_offset_));
    glColorPointer(4, GL_FLOAT, 0, BUFFER_OFFSET(sizeof(Vec3f)*colour_offset_));
    glVertexPointer(3, GL_FLOAT, 0, 0);

//    glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_SLICES*LENGTHWISE_SLICES*4*2);
    glDrawArrays(GL_QUADS, 0, VERTEX_COUNT);

    // Disable array mode
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}

uint dcTunnel::getSegmentFromPos(float depth)
{

}

void dcTunnel::setColour(const dcColour col)
{
    base_colour_ = col;
    dcColour coll = col;

    for (uint i=0; i<LENGTHWISE_SLICES; ++i)
    {
        coll.r = base_colour_.r - (base_colour_.r*i/LENGTHWISE_SLICES)*colour_decay_;
        coll.g = base_colour_.g - (base_colour_.g*i/LENGTHWISE_SLICES)*colour_decay_;
        coll.b = base_colour_.b - (base_colour_.b*i/LENGTHWISE_SLICES)*colour_decay_;

        for (uint j=0; j<CIRCLE_SLICES; ++j)
        {
            colour_array_[(i*CIRCLE_SLICES+j)*4+0] = coll;
            colour_array_[(i*CIRCLE_SLICES+j)*4+1] = coll;
            colour_array_[(i*CIRCLE_SLICES+j)*4+2] = coll;
            colour_array_[(i*CIRCLE_SLICES+j)*4+3] = coll;
        }
    }
    dcVBO::BindBufferARB(GL_ARRAY_BUFFER, vbo_id_);
    dcVBO::BufferSubDataARB(GL_ARRAY_BUFFER, sizeof(Vec3f)*colour_offset_, sizeof(dcColour)*(VERTEX_COUNT), colour_array_);
}
