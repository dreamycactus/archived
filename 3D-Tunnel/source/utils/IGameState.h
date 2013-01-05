#ifndef CGAMESTATE_H
#define CGAMESTATE_H


class IGameState
{
    public:
    virtual void                init() = 0;
    virtual void                cleanup() = 0;
    virtual void                tick(float delta) = 0;
    virtual void                render(float delta) = 0;

    protected:



//        virtual void Pause() = 0;
//        virtual void Resume() = 0;
//
//        virtual void HandleInput(CGameEngine* game) = 0;
//        virtual void Update(CGameEngine* game) = 0;
//        virtual void Draw(CGameEngine* game) = 0;

//        void ChangeState(CGameEngine* game, CGameState* state) { game->ChangeState(state); }
};

#endif // CGAMESTATE_H
