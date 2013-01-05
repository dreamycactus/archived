#ifndef STATE_CTRANSSQUARESPIN_H
#define STATE_CTRANSSQUARESPIN_H

#include "STATE_cGameTransition.hpp"

namespace CORE
{
    class cGame;
}

namespace STATE
{

    class cTransSquareSpin : public cGameTransition
    {
    public:
        cTransSquareSpin();
        virtual ~cTransSquareSpin();

        static   cGameTransition* CreateInstance() { return new cTransSquareSpin; }
        virtual  iGameState* Clone() {}

        bool    OnEnter(CORE::cGame* game);
        bool    OnExit(CORE::cGame* game);
        void    Pause(CORE::cGame* game){}
        void    Resume(CORE::cGame* game){}

        void    Update(CORE::cGame* game, float delta);

        void    Render(CORE::cGame* game, float percent_tick);
    private:
        float   m_PercentDone;
        float   m_AnimSpeed;

        bool    m_IsOldStateCleanup;



}; // End class cTransSquareSpin

} // End namespace STATE

#endif // STATE_CTRANSSQUARESPIN_H
