#ifndef SHOT_H
#define SHOT_H

#include <vector>
#include "../CGameEngine.h"
#include "../SDL_Helper.h"
#include "../CAnimation.h"
#include "../Runner.h"



class Shot : public Thing
{
    public:
        Shot() { Init(); }
        Shot(Vector2D pos, int duration, double top, double bot, std::vector<SDL_Rect> c, CAnimation a);
        void Init();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);


        void Cleanup() { SDL_FreeSurface(sprite_sheet); }
        void SetClip(std::vector<SDL_Rect> c) { clip = c; }
        void SetAnims(CAnimation a) { this->anim = a; }
        void Shoot() { active = true; }
        bool GetActive() { return active; }
    private:
        bool active;
        int duration;
        int elapsed;
        double top;
        double bot;
        CAnimation anim;
        SDL_Surface *sprite_sheet;
        std::vector<SDL_Rect> clip;

};

#endif // SHOT_H
