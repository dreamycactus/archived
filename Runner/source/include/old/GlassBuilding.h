#ifndef GLASSBUILDING_H
#define GLASSBUILDING_H

#include "SDL_Helper.h"
#include "Thing.h"
#include "Glass.h"
#include "Runner.h"

const Vector2D GLASS_BOX = Vector2D(40.0, 100.0);

class CGameEngine;

class GlassBuilding : public Thing
{
    public:
        GlassBuilding(){}
        GlassBuilding(Vector2D pos, Vector2D box, Vector2D posTop, Vector2D boxTop, bool glass);

        void Init();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);
        void Cleanup();

        Vector2D GetPosTop();
        Vector2D GetBoxTop();
        friend class Level;
        friend class GameScreen;

    private:
        double glassHeight;
        Glass *glasses[2];
        bool paneState[2];
        bool glass;
        Vector2D boxTop;
        Vector2D posTop;

        SDL_Surface *sprite_bot;
        SDL_Surface *sprite_inside;
        SDL_Surface *sprite_top;
};

#endif // GLASSBUILDING_H
