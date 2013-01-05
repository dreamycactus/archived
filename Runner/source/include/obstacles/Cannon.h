#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include "../Obstacle.h"
#include "../SDL_Helper.h"
#include "../CAnimation.h"
#include "../Runner.h"
#include "../Explosion.h"


const Vector2D CANNON_BEAM_OFFSET = Vector2D(584, 0);

using std::vector;

class Cannon : public Obstacle
{
    public:
        Cannon(Vector2D pos);
        void Init();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);
        void Cleanup();
        void Kill(int k);
        SDL_Rect* GetColBox();

        int GetState() { return state; }
        double GetDetectionRange() { return detectionRange; }

    private:

        Vector2D bulletPos;
        double detectionRange;
        double attackRange;
        bool weapActive, shot;
        int weapDuration;
        int weapElapsed;
        int shooterAlpha, shotOffset;
        int dieLoop, hp;
        double weapLevelMax, weapLevelMin;

        vector<Explosion*> explosions;
        CSoundEffect soundRev;
        CSoundEffect soundFire;
        SDL_Surface *sprite;
        SDL_Surface *sprite_beam;
        CAnimation anims[2], anim_beam;
        SDL_Rect clip_beam[5];
        SDL_Rect clip_neutral;
        SDL_Rect clip_alert[6];
        SDL_Rect clip_shoot[5];
};

#endif // CANNON_H
