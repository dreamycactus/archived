// Based on Kore input by Sean Chapel
// TODO: JOYSTICK RESPONSE CURVE
#ifndef INPUT_H
#define INPUT_H

// Headers
#include "global_inc.hpp"

#define JOY_MIN 8000.0f
#define JOY_MAX 32768.0f

namespace CORE
{

    class Input
    {
    public:
        struct JoyAxisExtent
        {
            std::array<float, 2> val;
        };
                        Input();
                        ~Input();

        bool            Initialise();
        bool            Terminate();

        void            HandleEvent(const SDL_Event& event);
        void            UpdateAll();

        bool    GetKeyState(int key);
        bool    OnKeyDown(int key);
        bool    OnKeyUp(int key);

        bool    GetMouseButtonState(int button);
        bool    OnMouseButtonDown(int button);
        bool    OnMouseButtonUp(int button);
        void    GetMousePos2(int& x, int& y);
        void    GetMouseDeltaXY(int& x, int& y);

        float   CalculateJoyExtents(float v);
        bool    GetJoyButtonState(const int whichJoy, const int button);
        bool    OnJoyButtonDown(const int whichJoy, const int button);
        bool    OnJoyButtonUp(const int whichJoy, const int button);
        void    GetJoyExtentIDWhichExtent2(const int whichJoy, const int whichStick, float& xExtent, float& yExtent);
        void    GetJoyDeltaXY(int& x, int& y);




    private:
        // Keyboard
        std::map<int, char> m_Keystates;	        /**< Holds the state of the keys */
        std::vector<SDL_Keycode> m_Recentkeys;

        // Mouse
        std::map<int, char> m_MouseButtonstates;
        std::vector<SDL_Keycode> m_RecentMouseButtons;
        int m_MouseX;
        int m_MouseY;

        // Joystick
        std::vector<SDL_Joystick*> m_pJoysticks;
        std::vector<std::map<int, char> > m_JoyButtonstates;
        std::vector<std::vector<SDL_Keycode>  > m_RecentJoyButtons;
        std::vector<std::array<float, 4> > m_JoyAxisExtents; //! Array of joysticks which each contain 2 XY axis sticks (2x2=4)
        int m_nJoysticks;

    }; // class Input

    inline bool Input::GetKeyState(int key)
    { return (m_Keystates[key]=='h' || m_Keystates[key]=='d') ? true : false; }

    inline bool Input::OnKeyDown(int key)
    { return (m_Keystates[key]=='d') ? true : false; }

    inline bool Input::OnKeyUp(int key)
    { return (m_Keystates[key]=='u') ? true : false; }

    inline bool Input::GetMouseButtonState(int button)
    { return (m_MouseButtonstates[button]=='h' || m_MouseButtonstates[button]=='d') ? true : false; }

    inline bool Input::OnMouseButtonDown(int button)
    { return (m_MouseButtonstates[button]=='d') ? true : false; }

    inline bool Input::OnMouseButtonUp(int button)
    { return (m_MouseButtonstates[button]=='u') ? true : false; }

    inline void Input::GetMousePos2(int& x, int& y)
    { x = m_MouseX; y = m_MouseY;  }

//    inline void GetMouseDeltaXY(int& x, int& y);

    inline bool Input::GetJoyButtonState(const int whichJoy, const int button)
    { return (m_JoyButtonstates[whichJoy][button]=='h' || m_JoyButtonstates[whichJoy][button]=='d') ? true : false; }

    inline bool Input::OnJoyButtonDown(const int whichJoy, const int button)
    { return (m_JoyButtonstates[whichJoy][button]=='d') ? true : false; }

    inline bool Input::OnJoyButtonUp(const int whichJoy, const int button)
    { return (m_JoyButtonstates[whichJoy][button]=='u') ? true : false; }

    inline float Input::CalculateJoyExtents(float v)
    { return (v>-JOY_MIN && v <JOY_MIN) ? 0.0f : v/JOY_MAX;   }

    inline void Input::GetJoyExtentIDWhichExtent2(const int whichJoy, const int whichStick, float& xExtent, float& yExtent)
    {
        const int offset = (whichStick*2);
        xExtent = CalculateJoyExtents(m_JoyAxisExtents[whichJoy][offset]);
        yExtent = CalculateJoyExtents(m_JoyAxisExtents[whichJoy][offset+1]);
    }

//    inline void GetJoyDeltaXY(int& x, int& y);

} // namespace CORE

#endif // INPUT_H
