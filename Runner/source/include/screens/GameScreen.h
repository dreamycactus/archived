#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <vector>
#include "../SDL_Helper.h"
#include "../CGameState.h"

#include "../Vector2D.h"
#include "../Collision.h"
#include "../Level.h"
#include "../Runner.h"
#include "../Building.h"
#include "../Background.h"
#include "../backgrounds/PlainBackground.h"
#include "../backgrounds/BillboardBackground.h"
#include "../backgrounds/Lightning.h"
#include "../backgrounds/TrainBackground.h"
#include "../backgrounds/Foreground.h"

//#include "MainMenuScreen.h"

using std::vector;

class GameScreen: public CGameState
{
    public:
        static GameScreen* instance() { return &inst; }
        bool Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleInput(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        void Reset();

        int GetFrames();
        void IncFrame();

        ~GameScreen();

    protected:
        GameScreen(){}

    private:
        static GameScreen inst;
        long frames;
        Level level;
        Runner player;
        int gameOverAlpha;

        SDL_Surface *gameOver;

        Mix_Music *music1;

        Lightning *light;
        vector<Background*> backgrounds;
        vector<Background*> foregrounds;


        Vector2D CorrectMacro(Vector2D ppos, Vector2D pbox, Vector2D pvel, Vector2D bpos, Vector2D bbox, bool &flag, bool &dead, bool *bumpHead = false);//I'm ashamed of this function so we make it private

        //GameScreen(GameScreen const&);              // Don't Implement
        //void operator=(GameScreen const&); // Don't implement

};

#endif // GAMESCREEN_H
