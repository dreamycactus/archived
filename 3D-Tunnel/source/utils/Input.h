#ifndef INPUT_H
#define INPUT_H

// Headers
#include <algorithm>
#include "SDL/SDL.h"
#include "SDL/SDL_main.h"
#include "keycodes.h"
class Input
{
    public:
//                            Input()                         { keystate_ = old_keystate_ = 0;}
//                            ~Input()                        { keystate_ = old_keystate_ = 0; }
    static  void            init()
    {
        std::fill(old_keystate_, old_keystate_ + HAR_LAST, 0);
        std::fill(keystate_, keystate_ + HAR_LAST, 0);
    }
    static  void            tick()
    {
        std::copy(keystate_, keystate_ + HAR_LAST, old_keystate_);
        std::copy(SDL_GetKeyboardState(0), SDL_GetKeyboardState(0) + HAR_LAST, keystate_);

        old_mouse_state_    = mouse_state_;
        old_mouse_x_        = mouse_x_;
        old_mouse_y_        = mouse_y_;
        mouse_state_        = SDL_GetMouseState(&mouse_x_, &mouse_y_);

    }

//    static  Uint8*          get_keystate()                  { return keystate_; }
//    static  Uint8*          get_old_keystate()              { return old_keystate_; }
    static  bool            key_down(int key)               { return keystate_[key]; }
    static  bool            key_just_pressed(int key)       { return (keystate_[key] && !old_keystate_[key]); }
    static  bool            key_just_released(int key)      { return (!keystate_[key] && old_keystate_[key]); }
    static  bool            mouse_just_pressed(int b)       { return ((mouse_state_&SDL_BUTTON(b)) && !(old_mouse_state_&SDL_BUTTON(b))); }
    static  bool            mouse_just_released(int b)      { return (!(mouse_state_&SDL_BUTTON(b)) && (old_mouse_state_&SDL_BUTTON(b))); }
    static  void            get_mouse_pos(int& x, int& y)   { x = mouse_x_; y = mouse_y_; }
    static  void            get_mouse_delta(int& x, int& y) { x = mouse_x_-old_mouse_x_; y = mouse_y_-old_mouse_y_; }

    protected:

    static  Uint8           old_keystate_[HAR_LAST];
    static  Uint8           keystate_[HAR_LAST];
    static  Uint8           old_mouse_state_;
    static  Uint8           mouse_state_;
    static  int             old_mouse_x_, old_mouse_y_;
    static  int             mouse_x_, mouse_y_;
};


#endif // INPUT_H
