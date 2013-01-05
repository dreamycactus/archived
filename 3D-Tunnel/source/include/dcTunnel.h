#ifndef DCTUNNEL_H
#define DCTUNNEL_H

// Headers
#include <gl/gl.h>
#include "mytypes.h"
#include "tokens/CMaterial.h"

class dcTunnel
{
    public:
        // Members -- kinda constants
        uint                    CIRCLE_SLICES;
        uint                    LENGTHWISE_SLICES;
        uint                    VERTEX_COUNT;
        float                   RADIUS;
        float                   SEGMENT_LENGTH;

        // Methods
                                dcTunnel();
                                dcTunnel(uint c_slice, uint l_slice, float radius, float seg_len);
        virtual                 ~dcTunnel();

        void                    init(uint c_slice, uint l_slice, float radius, float seg_len);
        void                    buildTunnel();
        void                    render();

        void                    recalculateVertexCount() { VERTEX_COUNT = LENGTHWISE_SLICES*CIRCLE_SLICES*4; }
        // Getters
        uint                    getSegmentFromPos(float depth);

        void                    setColour(const dcColour col);


    private:
        dcColour                base_colour_;
        float colour_decay_;
        dcColour*               colour_array_;
        uint                    colour_array_sz_;

        uint                    normal_offset_;
        uint                    colour_offset_;

        GLuint                  vbo_id_;
        uint                    index_;
        bool                    built_;
        CMaterial               material_;
};

#endif // DCTUNNEL_H
