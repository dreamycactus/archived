#include "../../include/CGameState.h"
#include "../../include/screens/GameScreen.h"
#include "../../include/screens/MainMenuScreen.h"
#include "../../include/screens/GameOverScreen.h"



GameScreen GameScreen::inst;

GameScreen::~GameScreen()
{

}
bool GameScreen::Init()
{
    unsigned int i;
    gameOverAlpha = 0;
    gameOver = load_image("sprites/black.png");
    vector<string> temp;
    vector< vector <double> > yLines;
    vector<double> tempY;
    vector<Bounds> xBounds;

    temp.push_back("sprites/backgrounds/bg_clouds.png");
    backgrounds.push_back(new PlainBackground(temp, 0, 0, 0.05));
    temp.clear();
    temp.push_back("sprites/backgrounds/bg4_1.png");
    temp.push_back("sprites/backgrounds/bg4_2.png");
    backgrounds.push_back(new PlainBackground(temp, 130, 15, 0.2));
    temp.clear();
    temp.push_back("sprites/backgrounds/bg3_1.png");
    temp.push_back("sprites/backgrounds/bg3_2.png");
    temp.push_back("sprites/backgrounds/bg3_3.png");
    backgrounds.push_back(new PlainBackground(temp, 200, 30, 0.25));
    temp.clear();

    /* Spawn Train Layer*/

    backgrounds.push_back(new TrainBackground(0.22));

    /* Spawn Billbord */

    tempY.push_back(37); //insert a valid height for a bird spawn on a billboard
    yLines.push_back(tempY); //push the whole vector in...
    tempY.clear(); //clear the temporary vector
    xBounds.push_back(Bounds(140, 285)); // set the x bounds for bird spawn
    temp.push_back("sprites/backgrounds/bill_die.png");

    tempY.push_back(40);
    tempY.push_back(146);
    yLines.push_back(tempY);
    tempY.clear();
    xBounds.push_back(Bounds(80, 360));
    temp.push_back("sprites/backgrounds/bill_drugs.png");

    tempY.push_back(45);
    tempY.push_back(125);
    yLines.push_back(tempY);
    tempY.clear();
    xBounds.push_back(Bounds(130, 315));
    temp.push_back("sprites/backgrounds/bill_eva.png");

    tempY.push_back(51);
    tempY.push_back(120);
    yLines.push_back(tempY);
    tempY.clear();
    xBounds.push_back(Bounds(80, 360));
    temp.push_back("sprites/backgrounds/bill_speed.png");

    tempY.push_back(62);
    yLines.push_back(tempY);
    tempY.clear();
    xBounds.push_back(Bounds(110, 320));
    temp.push_back("sprites/backgrounds/bill_watch.png");
    backgrounds.push_back(new BillboardBackground(temp, yLines, xBounds, 0, 250, 0.4));
    temp.clear();

    yLines.clear();
    xBounds.clear();
    /*Done Billboards PHEW */

    foregrounds.push_back(new Foreground(0, 1.2));

    /*Init Stuff */
    level.Init();
    player.Init();
    for (i = 0; i < backgrounds.size(); ++i)
        backgrounds[i]->Init();

    light = new Lightning();

//    rainDrop = load_image("sprites/rainDrop.png");

    music1 = Mix_LoadMUS("sounds/gametrack.mp3");
    frames = 0;
    return true;
}



void GameScreen::Pause(){}
void GameScreen::Resume(){}

void GameScreen::HandleInput(CGameEngine* game)
{
    Uint8 *keystates = SDL_GetKeyState(NULL);
    SDL_Event event = game->GetEvent();
    if( event.type == SDL_KEYDOWN )
    {
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
            game->ChangeState(MainMenuScreen::instance());
            return;
        }

    }
    player.HandleInput();

}

Vector2D GameScreen::CorrectMacro(Vector2D ppos, Vector2D pbox, Vector2D pvel, Vector2D bpos, Vector2D bbox, bool &onGround, bool &crashed, bool *bumpHead)
{
    Vector2D correct = FixCol(ppos, pbox, pvel, bpos, bbox, onGround, crashed, bumpHead);
    return correct;
}


void GameScreen::Update(CGameEngine* game)
{
    Vector2D velocity = player.GetVelocity();
    Vector2D correct(0.0, 0.0);

    bool onGround = false;
    bool crashed = false;
    bool stumble = false;

    if( Mix_PlayingMusic() == 0 ) { Mix_PlayMusic( music1, -1 ); }
    //check player collision with buildings
    for (unsigned int i = 0; i < level.buildings.size(); ++i)
    {
        if (CheckCol(player.GetPos(), player.GetBox(),  velocity + GRAVITY + player.NextSpeed(), level.buildings[i]->GetColPos(), level.buildings[i]->GetBox()))
        {
            correct = CorrectMacro(player.GetPos(), player.GetBox(),  velocity + GRAVITY + player.NextSpeed(), level.buildings[i]->GetColPos(), level.buildings[i]->GetBox(), onGround, crashed);
            break;
        }
    }


    player.SetOnGround(onGround);
    player.SetCrashed(crashed);

    //if there was collision corect velocity by moving player as close as possible to collided object
    velocity += correct + GRAVITY + player.NextSpeed(); //apply forces/speed to player

    player.SetVelocity(velocity);
    level.Update(game, &player);
    player.Update(game, level.buildings.back(), level.GetNextObstacle(&player));
    ++frames;
    light->Update(player.GetPos());
    for (unsigned int i = 0; i < backgrounds.size(); ++i)
        backgrounds[i]->Update(game, player.GetDrawX());
    for (unsigned int i = 0; i < foregrounds.size(); ++i)
        foregrounds[i]->Update(game, player.GetDrawX());



}
double Scale(double pos, int mod, double scale)
{
    return (double)((int)(pos * scale) % mod);
}
void GameScreen::Draw(CGameEngine* game)
{
    unsigned int i;

    //Fill the screen white
    SDL_FillRect( game->GetScreen(), &game->GetScreen()->clip_rect, SDL_MapRGB( game->GetScreen()->format, 0xFF, 0xFF, 0xFF ) );

    for (i = 0; i < backgrounds.size(); ++i)
        backgrounds[i]->Draw(game, player.GetDrawX());

    light->Draw(game, player.GetDrawX()); //draw lightning

    level.Draw(game, &player); //draw level

    player.Draw(game); //draw player

    for (i = 0; i < foregrounds.size(); ++i)
        foregrounds[i]->Draw(game, player.GetDrawX());

    light->Flash(game); //if lightning is flashing, make screen white


    if (player.GAMEOVER)
    {
        gameOverAlpha += 5;
        SDL_SetAlpha(gameOver, SDL_SRCALPHA, gameOverAlpha);
        apply_surface(Vector2D(0,0), gameOver, game->GetScreen());
        if (gameOverAlpha >= 255)
            game->ChangeState(GameOverScreen::instance());
    }


}

void GameScreen::Cleanup()
{
    /* Free Surfaces HERE*/
    Mix_FreeMusic(music1);
    unsigned int i;
    for (i = 0; i < backgrounds.size(); ++i)
    {
        backgrounds[i]->Cleanup();
        delete backgrounds[i];
    }
    for (i = 0; i < foregrounds.size(); ++i)
    {
        foregrounds[i]->Cleanup();
        delete foregrounds[i];
    }

    backgrounds.clear();
    foregrounds.clear();

    player.Cleanup();
    level.Cleanup();
    light->Cleanup();
    delete light;

}
void GameScreen::Reset()
{
    player.Reset();
    level.Reset();
}

int GameScreen::GetFrames()
{
    return frames;
}
void GameScreen::IncFrame()
{
    ++frames;
}


