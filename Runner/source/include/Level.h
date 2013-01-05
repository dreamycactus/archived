#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "SDL_Helper.h"
#include "CAnimation.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Runner.h"
#include "Building.h"
#include "Obstacle.h"
#include "Doodad.h"

#include "obstacles/Shooter.h"
#include "obstacles/Cannon.h"
#include "obstacles/Sentry.h"
#include "obstacles/PlainObstacle.h"


#define PLAT_LAMP        0
#define PLAT_GIRDER      1
#define PLAT_ICE         2
#define PLAT_ROCK        3
#define PLAT_GEAR        4

class CGameEngine;
class GameScreen;

const int ENEMY_GROWTH = 40;

using namespace std;

class Plat
{
    public:
        Plat(string f, int np, double s)
        {
            fileName = f;
            numPieces = np;
            surfaceLevel = s;

        }
        string fileName;
        double surfaceLevel;
        int numPieces;

};

class Level
{
    public:
        Level();

        bool Init();
        void Update(CGameEngine *game, Runner *player);
        void Draw(CGameEngine *game, Runner *player);
        void Generate(Vector2D pos, Vector2D velocity, int screen_w);
        void Cleanup();
        void Reset();

        Obstacle* GetNextObstacle(Runner *player);

        vector<Obstacle*> GetObstacles();

        friend class GameScreen;
    protected:
    private:
        vector<Building*> buildings;
        vector<Obstacle*> obstacles;
        vector<Plat> platNames;
        vector<Doodad*> doodads;

        int currentPlat, numObstaclesBeaten;
        SDL_Surface *build1_sprite;
        SDL_Surface *box_sprite;
};

#endif // LEVEL_H
