#ifndef RUNNER_H
#define RUNNER_H


#include "Vector2D.h"
#include "SDL_Helper.h"
#include "CGameEngine.h"
#include "CGameState.h"
#include "Obstacle.h"
#include "Thing.h"
#include "Building.h"
#include "CAnimation.h"

//The dimenstions of the stick figure
const double FOO_WIDTH = 16.0;
const double FOO_HEIGHT = 53;
const int SPRITE_SIDE = 50, INVINCIBLE_TIME = 50;
const Vector2D GRAVITY = Vector2D(0.0, 4.5);
const double STEP = 0.06;

//mode
#define GRAVE            0
#define MARIA            1

//char status
#define C_OK            0
#define C_DAZE          1
#define C_DEAD          2

//player state

#define S_RUN           0
#define S_CROUCH        1
#define S_SHOOT         2
#define S_JUMP_START    3
#define S_JUMP_FINISH   4
#define S_STUMBLE     5
#define S_DEAD          6
#define S_SWAP          7

//player actions
#define A_RUN          0
#define A_JUMP         1
#define A_CROUCH       2
#define A_SHOOT        3
#define A_STUMBLE      4
#define A_SWAP         5

#define SOUND_JUMP    0
#define SOUND_SHOOT   1
#define SOUND_SLIDE   2
#define SOUND_SWAP    3

const int NUM_ACTIONS = 6;
const int DAZE_TIME = 240;
const double GUN_HEIGHT = 15.0;
const int SWORD_INVINCIBLE = 9;
const int SWAP_TIME = 120;

const Vector2D START_POS = Vector2D(100, 0);
const double MAX_SPEED = 30.0;

const Vector2D BOX_RUN= Vector2D(FOO_WIDTH, FOO_HEIGHT);
const Vector2D BOX_CROUCH = Vector2D(FOO_HEIGHT, FOO_WIDTH);
const Vector2D ADJUST_CROUCH = Vector2D(0.0, FOO_HEIGHT - FOO_WIDTH);

class Building;
class Obstacle;

using std::vector;

class Runner : public Thing
{
    public:
        Runner();

        void Init();
        void Move();
        bool Jump();
        void HandleInput();
        void Update(CGameEngine *game, Building *lastBuilding, Obstacle *enemy);
        Vector2D NextSpeed();
        void Cleanup();
        void Draw(CGameEngine* game);
        void Reset();
        void SetAction(int action);

        void Stumble();
        void Swap();

        Vector2D GetPosX();
        Vector2D GetPosY();
        Vector2D GetVelocity();
        int GetState();
        int GetFrame();
        int GetMode() { return mode; }
        double GetGunRange() { return gunRange[mode]; }

        //Setters
        void SetState(int state);
        void SetFrame(int frame);
        void SetVelocity(Vector2D velocity);
        void SetOnGround(bool b);
        void SetCrashed(bool b);
        Vector2D GetPos();
        Vector2D GetDrawX();
        Vector2D GetDrawY();
        bool GAMEOVER;

    private:

        Vector2D velocity;

        int state;
        bool showChar[2];
        double gunRange[2];
        double slideFriction[2]; //different coefficients for each char
        double jumpFactor[2];
        double jumpLen[2];
        int jumpTime[2];
        int charState[2];
        bool onGround;
        bool crashed;

        int mode;
        bool action[NUM_ACTIONS]; //4 actions, jump, slide etc
        bool animTransDone[NUM_ACTIONS]; //for the 4 actions
        int frameChangeRate[NUM_ACTIONS];//for each of 4 actions
        SDL_Rect collisionBox[NUM_ACTIONS];

        bool swapping;
        int currentAction; //current action index for some arrays
        int miniTimer; //a timer for delaying the swapping animation a bit
        int invTimer; //invincibility timer
        int mariaSwordTimer;
        int swapTimer;
        int jumpTimer;
        int dazeTimer[2];
        Vector2D tempAnchor; //to store the temporary positions of the swapping out character
        Vector2D tempPosG;
        Vector2D tempPosM;

        CAnimation anims[NUM_ACTIONS];
        CAnimation swap;
        CAnimation animSword;

        SDL_Surface *grave_sprite;
        SDL_Surface *maria_sprite;
        SDL_Surface *poof_sprite;
        SDL_Surface *bullet_sprite;
        SDL_Surface *sword_sprite;
        SDL_Surface *temp;

        SDL_Rect tempRect;
        vector< vector<SDL_Rect> > clips;
        vector<SDL_Rect> swordClip;
        vector< vector<CSoundEffect> > soundEffects;
        CSoundEffect soundHit;

};

#endif // RUNNER_H
