#ifndef SHOOTER_H
#define SHOOTER_H

#include <vector>
#include "../Obstacle.h"
#include "../SDL_Helper.h"
#include "../CAnimation.h"
#include "../Runner.h"


#define MAX_DIE           1
const int SH_NUM_ACTIONS = 3;


class CGameEngine;


class Shooter : public Obstacle
{
    public:
        Shooter(Vector2D pos);
        void Init();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);
        void Kill(int k);
        void Cleanup();
        SDL_Rect* GetColBox();

        int GetState() { return state; }
        double GetDetectionRange() { return detectionRange; }

    private:

        Vector2D bulletPos;
        double detectionRange;
        double attackRange;
        double laserEnd;
        bool weapActive;
        int weapDuration;
        int weapElapsed;
        int trailAlpha;
        int shotOffset;
        int shooterAlpha;
        int dieLoop;
        double weapLevel;

        SDL_Surface *sprite_sheet;
        SDL_Surface *weap_sprite_sheet;
        SDL_Surface *laser_sprite;
        CAnimation anims;
        SDL_Rect clip_neutral;
        SDL_Rect clip_alert;
        SDL_Rect clip_shoot[3];

        CSoundEffect laserhumSound;
        CSoundEffect shootSound;
};

#endif // SHOOTER_H
