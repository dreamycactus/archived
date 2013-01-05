#include "CORE_cSDLState.hpp"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

using namespace CORE;

cSDLState::cSDLState(int win_w, int win_h)
{
    init();
    window_w = win_w;
    window_h = win_h;
}

cSDLState::cSDLState()
{
    init();
}

void cSDLState::init()
{
    window = 0;
    renderer = 0;
    glctx = 0;

    window_title = "";
    window_x = SDL_WINDOWPOS_CENTERED;
    window_y = SDL_WINDOWPOS_CENTERED;
    window_w = DEFAULT_WINDOW_WIDTH;
    window_h = DEFAULT_WINDOW_HEIGHT;
    is_fullscreen = SDL_FALSE;

    SDL_zero(render_flags);

    /* Set some very sane GL defaults */
    gl_major_version = 3;
    gl_minor_version = 1;

    gl_red_size = 3;
    gl_green_size = 3;
    gl_blue_size = 2;
    gl_alpha_size = 0;
    gl_buffer_size = 0;
    gl_depth_size = 16;
    gl_stencil_size = 0;
    gl_double_buffer = 1;
    gl_accum_red_size = 0;
    gl_accum_green_size = 0;
    gl_accum_blue_size = 0;
    gl_accum_alpha_size = 0;
    gl_stereo = 0;
    gl_multisamplebuffers = 0;
    gl_multisamplesamples = 0;
    gl_retained_backing = 1;
    gl_accelerated = 1;

}

cSDLState::~cSDLState()
{
}

void cSDLState::SetGL()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, gl_red_size);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, gl_green_size);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, gl_blue_size);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, gl_alpha_size);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, gl_double_buffer);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, gl_buffer_size);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, gl_depth_size);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, gl_stencil_size);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, gl_accum_red_size);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, gl_accum_green_size);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, gl_accum_blue_size);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, gl_accum_alpha_size);
    SDL_GL_SetAttribute(SDL_GL_STEREO, gl_stereo);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, gl_multisamplebuffers);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, gl_multisamplesamples);

    if (gl_major_version) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_version);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_version);
    }
    if (gl_accelerated >= 0) {
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    }
    SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, gl_retained_backing);

}
