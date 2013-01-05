#include "Input.h"

Uint8   Input::old_keystate_[HAR_LAST];
Uint8   Input::keystate_[HAR_LAST];
Uint8   Input::old_mouse_state_;
Uint8   Input::mouse_state_;
int     Input::old_mouse_x_;
int     Input::old_mouse_y_;
int     Input::mouse_x_;
int     Input::mouse_y_;
