#include "../include/Level.h"



Level::Level()
{
    //tunnels.push_back(GlassBuilding(Vector2D(1000, 380), Vector2D(200, 200), Vector2D(1000, 80), Vector2D(200, 200), true));

}

bool Level::Init()
{
    unsigned int i = RandInt(0, 4);
    numObstaclesBeaten = 0;
    Vector2D v(0, 0);

    platNames.push_back(Plat("sprites/platforms/plat1.png", 3, 30));
    platNames.push_back(Plat("sprites/platforms/plat2.png", 3, 434));
    platNames.push_back(Plat("sprites/platforms/plat3.png", 4, 198));
    platNames.push_back(Plat("sprites/platforms/plat4.png", 5, 174));
    platNames.push_back(Plat("sprites/platforms/plat5.png", 6, 146));

    doodads.push_back(new Doodad("sprites/doodads/deco_bench.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_arrow.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_bus.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_end.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_lamp.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_monster.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_p.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_run.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_swing.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_tank.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_tank_shatter.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_torch.png", v));
    doodads.push_back(new Doodad("sprites/doodads/deco_traffic.png", v));



    buildings.push_back(new Building(Vector2D(0, 280), 25, platNames[i].surfaceLevel, platNames[i].numPieces, platNames[i].fileName));

    currentPlat = i;
    build1_sprite = load_image("sprites/build1.png");
    box_sprite = load_image("sprites/box.png");
    srand((unsigned)time(NULL));

    return true;
}

void Level::Update(CGameEngine *game, Runner *player)
{
    unsigned int i, j;
    Generate(player->GetPos(), player->GetVelocity(), game->GetWidth());
    for (i = 0; i < buildings.size(); ++i) //erase buildings that are behind us
    {
        if (buildings[i]->GetDrawPos().x+buildings[i]->GetBox().x + START_POS.x + 500 < player->GetDrawX().x)
        {
            buildings[i]->Cleanup();
            buildings.erase(buildings.begin()+i);
            break;
        }
        else
            break;
    }

    vector<Obstacle*>::iterator iter;
    for (iter = obstacles.begin(); iter != obstacles.end(); ) //erase obstacles that are behind us
    {
        if (obstacles[i]->GetPos().x + 150 + START_POS.x < player->GetDrawX().x || obstacles[i]->GetState() == SO_DELETE)
        {
            obstacles[i]->Cleanup();
            delete obstacles[i];
            iter = obstacles.erase(iter);
        }
        else
            ++iter;
    }

    for (i = 0; i < obstacles.size(); ++i)
    {
        obstacles[i]->Update(game, player);
    }
    for (i = 0; i < doodads.size(); ++i)
    {
        doodads[i]->Update(player->GetPos());
    }

}

void Level::Draw(CGameEngine *game, Runner *player)
{
    unsigned int i;
    for (i = 0; i < buildings.size(); ++i)
    {
        buildings[i]->Draw(game, player);
    }
    for (i = 0; i < doodads.size(); ++i)
    {
        doodads[i]->Draw(game, player->GetDrawX());
    }
    for (i = 0; i < obstacles.size(); ++i)
    {
        obstacles[i]->Draw(game, player);
    }
}

void Level::Generate(Vector2D pos, Vector2D velocity, int screen_w)
{
    double bright = buildings.back()->GetColPos().x + buildings.back()->GetBox().x;

    if (pos.x + screen_w - START_POS.x + velocity.x < bright)
        return;

    /* Spawn Building */


    double p_height = RandDouble(max(buildings.back()->GetColPos().y - 50, 200),
                                 min((int)buildings.back()->GetColPos().y + 50, 400)), //height of platform
    p_dist = RandDouble(100, 250); //distance from current platform
    int p_len = RandInt(20, 110); //number of blocks in plat

    int platSpawn = RandInt(0, platNames.size() - 1), //type of plat to spawn
    keep = RandInt(0, 9); //just a random percentage --1/9
    currentPlat = (keep != 0) ? platSpawn : currentPlat; // more likely to spawn the curret platform type



    buildings.push_back(new Building(Vector2D(bright + p_dist, p_height), p_len, platNames[currentPlat].surfaceLevel, platNames[currentPlat].numPieces, platNames[currentPlat].fileName));

    /* Spawn Obstacles */

    int numObstacles = RandInt((int) p_len/60, (int) p_len/30);
    Vector2D tPos(0, 0);
    int obstacleType, plainType;
    double platPos = buildings.back()->GetColPos().x + RandDouble(700, 2000),
           endPos = buildings.back()->GetColPos().x + buildings.back()->GetBox().x,
           nextPos = RandDouble(800, 1300);
    while(platPos + nextPos < endPos)
    {
        obstacleType = RandInt(0, 3);
        string temp;
        tPos = Vector2D(platPos, buildings.back()->GetColPos().y);
        ++numObstaclesBeaten;
        switch(obstacleType)
        {
            case SHOOTER:
                obstacles.push_back(new Shooter(tPos + Vector2D(0, -50)));
                break;
            case CANNON:
                obstacles.push_back(new Cannon(tPos + Vector2D(0, -105)));
                break;
            case SENTRY:
                obstacles.push_back(new Sentry(tPos + Vector2D(0, -59)));
                break;
            case PLAIN:
                plainType = RandInt(0, 1);
                if (plainType == 0)
                    temp = "sprites/obstacles/dogman.png";
                else
                    temp = "sprites/obstacles/chainsaw.png";

                obstacles.push_back(new PlainObstacle(tPos + Vector2D(0, -45), temp, plainType));
                break;
        }
        platPos += nextPos;
        nextPos = RandDouble(350, max(3000-ENEMY_GROWTH*numObstaclesBeaten, 600));
    }

    int numDoodads = RandInt((int) 1, (int) 11);
    int countDoodads = 0, i, x = 0;

    while (countDoodads <= numDoodads && x < 14)
    {
        ++x;
        i = RandInt(0, doodads.size()-1);
        if (!doodads[i]->Showing() && countDoodads < 14)
        {
            tPos = Vector2D(RandDouble(buildings.back()->GetColPos().x + 200, buildings.back()->GetColPos().x + buildings.back()->GetBox().x - 200), buildings.back()->GetColPos().y);
            ++countDoodads;
            doodads[i]->SetPos(tPos);
        }


    }

}

Obstacle* Level::GetNextObstacle(Runner *player)
{
    Vector2D pos = player->GetPos();
    double gunRange = player->GetGunRange();
    int minIndex = -1;
    int minPos = pos.x + gunRange;

    for (unsigned int i = 0; i < obstacles.size(); ++i)
    {
        Vector2D pp = obstacles[i]->GetPos();
        SDL_Rect *b = obstacles[i]->GetColBox();
        if (pp.x - pos.x + START_POS.x < gunRange //enemy within range
        &&  pp.x + (double)b->w - pos.x + START_POS.x > 0 //enemy not behind
        &&  pp.y + (double)b->y < pos.y + GUN_HEIGHT //enemy at right level
        &&  pp.y + (double)b->y + (double)b->h > pos.y + GUN_HEIGHT) //same ^^
        {
            if (minPos > obstacles[i]->GetPos().x && obstacles[i]->GetState() != SO_DEAD)
            {
                minIndex = i;
                minPos = obstacles[i]->GetPos().x;
            }
        }

    }
    if (minIndex != -1)
        return obstacles[minIndex];
    return NULL;
}
void Level::Cleanup()
{
    SDL_FreeSurface(build1_sprite);
    SDL_FreeSurface(box_sprite);
    unsigned int i;

    for(i = 0; i < obstacles.size(); ++i)
    {
        obstacles[i]->Cleanup();
        delete obstacles[i];
    }
    for(i = 0; i < buildings.size(); ++i)
    {
        buildings[i]->Cleanup();
        delete buildings[i];
    }
    for(i = 0; i < doodads.size(); ++i)
    {
        doodads[i]->Cleanup();
        delete doodads[i];
    }

    buildings.clear();
    obstacles.clear();
    platNames.clear();
    doodads.clear();

}

void Level::Reset()
{

}

vector<Obstacle*> Level::GetObstacles()
{
    return obstacles;
}
