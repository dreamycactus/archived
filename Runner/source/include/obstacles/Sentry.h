#ifndef SENTRY_H
#define SENTRY_H

#include <vector>
#include "../Obstacle.h"
#include "../SDL_Helper.h"
#include "../CAnimation.h"
#include "../Runner.h"
#include "../Explosion.h"

const Vector2D SENTRY_BEAM_OFFSET = Vector2D(584, -5);

using std::vector;

class Sentry : public Obstacle
{
    public:
        Sentry(Vector2D pos);
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
        CSoundEffect sound;
        CSoundEffect pew;
        SDL_Surface *sprite;
        SDL_Surface *sprite_beam;
        CAnimation anim_beam;
        SDL_Rect clip_beam[15];
};

#endif // SENTRY_H
