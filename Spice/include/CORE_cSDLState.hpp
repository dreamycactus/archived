/**
* Contains Window and Renderer Info - Taken from common.h in the SDL test code from the Mercurial repo.
* Intended to be a data-only class
**/
#ifndef CORE_CSDLSTATE_H
#define CORE_CSDLSTATE_H

#include <SDL2/SDL.h>

namespace CORE
{


    class cSDLState
    {
    public:
        cSDLState(int win_w, int win_h); //alternate ctor for optional window width/height
        cSDLState();
        virtual ~cSDLState();
        void SetGL();
        void setWindowWidth(int val)
        {window_w = val;};
        void setWindowHeight(int val)
        {window_h = val;};

    // Members

        /* Video info */
        const char* videodriver;    //!< Video driver to initialize SDL_Video. Optional.
        int display;
        const char* window_title;
        const char* window_icon;
        Uint32 window_flags;        //!< SDL Window flags
        int window_x;               //! Top left coords
        int window_y;
        int window_w;
        int window_h;
        int depth;                  //! Colour depth
        int refresh_rate;

        SDL_Window *window;         //!< May add more windows by making this an array

        /* Renderer info */
        const char* renderdriver;   //! Driver for rendering? Optional
        Uint32 render_flags;
        SDL_bool skip_renderer;     //! Don't use any renderer?
        SDL_bool is_fullscreen;
        SDL_Renderer* renderer; //! The context for renderer (OpenGl) << Set to current window w/ SDL_GL_MakeCurrent
        SDL_GLContext glctx;

        /* Audio info */
        const char* audiodriver;
        SDL_AudioSpec audiospec;

        /* GL settings */
        int gl_red_size;
        int gl_green_size;
        int gl_blue_size;
        int gl_alpha_size;
        int gl_buffer_size;
        int gl_depth_size;
        int gl_stencil_size;
        int gl_double_buffer;
        int gl_accum_red_size;
        int gl_accum_green_size;
        int gl_accum_blue_size;
        int gl_accum_alpha_size;
        int gl_stereo;
        int gl_multisamplebuffers;
        int gl_multisamplesamples;
        int gl_retained_backing;
        int gl_accelerated;
        int gl_major_version;
        int gl_minor_version;

    private:
        void init();

    }; // End class cSDL_State

} // End namespace CORE

#endif // CORE_CSDLSTATE_H
