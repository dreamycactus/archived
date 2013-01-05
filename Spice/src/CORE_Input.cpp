#include "CORE_Input.hpp"

using namespace CORE;

Input::Input()
: m_Keystates(), m_Recentkeys()
, m_MouseButtonstates(), m_RecentMouseButtons()
, m_MouseX(0), m_MouseY(0)
, m_pJoysticks(0)
, m_JoyButtonstates(), m_RecentJoyButtons()
, m_JoyAxisExtents()
{ }

Input::~Input()
{
    Terminate();
}

bool Input::Initialise()
{
    m_nJoysticks = SDL_NumJoysticks();

    m_pJoysticks.reserve(m_nJoysticks);          // Optional
    m_JoyButtonstates.reserve(m_nJoysticks);
    m_RecentJoyButtons.reserve(m_nJoysticks);

    if (m_nJoysticks<=0)
        std::cout << "WARNING. There are no joysticks!\n";

    for (int i=0; i<m_nJoysticks; ++i) {
        m_pJoysticks.push_back(0);
        m_pJoysticks[i] = SDL_JoystickOpen(i);
        m_JoyButtonstates.push_back(std::map<int, char>());
        m_JoyAxisExtents.push_back(std::array<float, 4>());
        m_RecentJoyButtons.push_back(std::vector<SDL_Keycode>());
        if (!m_pJoysticks[i]) {
            return false;
        }
    }

}

bool Input::Terminate()
{
    for (int i=0; i<m_nJoysticks; ++i) {
        if (m_pJoysticks[i]) {
            SDL_JoystickClose(m_pJoysticks[i]);
        }
    }
    m_pJoysticks.clear();
}

void Input::HandleEvent(const SDL_Event& event)
{
    Uint8 joyid, joyaxis;

    switch(event.type)
    {
        case SDL_KEYDOWN:
            m_Keystates[event.key.keysym.sym] = 'd';
            m_Recentkeys.push_back(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            m_Keystates[event.key.keysym.sym] = 'u';
            m_Recentkeys.push_back(event.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            m_MouseX = event.motion.x;
            m_MouseY = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_MouseButtonstates[event.button.button] = 'd';
            m_RecentMouseButtons.push_back(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            m_MouseButtonstates[event.button.button] = 'u';
            m_RecentMouseButtons.push_back(event.button.button);
            break;

        case SDL_JOYBUTTONDOWN:
            joyid = static_cast<int>(event.jbutton.which);

            m_JoyButtonstates[joyid][event.jbutton.button] = 'd';
            m_RecentJoyButtons[joyid].push_back(event.jbutton.button);
            break;
        case SDL_JOYBUTTONUP:
            joyid = event.jbutton.which; assert(joyid<m_nJoysticks);

            m_JoyButtonstates[joyid][event.jbutton.button] = 'u';
            m_RecentJoyButtons[joyid].push_back(event.jbutton.button);
            break;
        case SDL_JOYAXISMOTION:
//            if (event.jaxis.axis == 0) std::cout <<  event.jaxis.value << std::endl;
            joyid = static_cast<int>(event.jaxis.which); assert(joyid<m_nJoysticks);
            joyaxis = static_cast<int>(event.jaxis.axis);

            m_JoyAxisExtents[joyid][joyaxis] = static_cast<float>(event.jaxis.value);
            break;
        default:
            break;
    }
}


void Input::UpdateAll()
{
    // Keyboard
    for (std::map<int, char>::iterator it = m_Keystates.begin(); it != m_Keystates.end(); ++it) {
        bool keyFound = false;

        if (it->second == 'u') {
            for (int i=0; i<m_Recentkeys.size(); ++i) {
                if (m_Recentkeys[i] == it->first) {
                    keyFound = true;
                    break;
                }
            }
            if (!keyFound) {
                it->second = 'n';
            }
        } else if(it->second == 'd') {
            for (int i=0; i<m_Recentkeys.size(); ++i) {
                if(m_Recentkeys[i] == it->first) {
                    keyFound = true;
                    break;
                }
            }
            if ( !keyFound ) {
                it->second = 'h';
            }
        }
    }

    // Mouse
    for (std::map<int, char>::iterator it = m_MouseButtonstates.begin(); it != m_MouseButtonstates.end(); ++it) {
        bool keyFound = false;

        if (it->second == 'u') {
            for (int i=0; i<m_RecentMouseButtons.size(); ++i) {
                if (m_RecentMouseButtons[i] == it->first) {
                    keyFound = true;
                    break;
                }
            }
            if (!keyFound) {
                it->second = 'n';
            }
        } else if(it->second == 'd') {
            for (int i=0; i<m_RecentMouseButtons.size(); ++i) {
                if(m_RecentMouseButtons[i] == it->first) {
                    keyFound = true;
                    break;
                }
            }
            if ( !keyFound ) {
                it->second = 'h';
            }
        }
    }

    for (int j=0; j<m_pJoysticks.size(); ++j) {
        for (std::map<int, char>::iterator it = m_JoyButtonstates[j].begin(); it != m_JoyButtonstates[j].end(); ++it) {
            bool keyFound = false;

            if (it->second == 'u') {
                for (int i=0; i<m_RecentJoyButtons[j].size(); ++i) {
                    if (m_RecentJoyButtons[j][i] == it->first) {
                        keyFound = true;
                        break;
                    }
                }
                if (!keyFound) {
                    it->second = 'n';
                }
            } else if(it->second == 'd') {
                for (int i=0; i<m_RecentJoyButtons[j].size(); ++i) {
                    if(m_RecentJoyButtons[j][i] == it->first) {
                        keyFound = true;
                        break;
                    }
                }
                if ( !keyFound ) {
                    it->second = 'h';
                }
            }
        }
    }


    m_Recentkeys.clear();
    m_RecentMouseButtons.clear();
    for (int j=0; j<m_pJoysticks.size(); ++j) {
        m_RecentJoyButtons[j].clear();
    }
}
