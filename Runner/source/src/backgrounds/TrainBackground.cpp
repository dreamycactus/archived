#include "../../include/backgrounds/TrainBackground.h"

TrainBackground::TrainBackground(double sr)
{
    scrollRate = sr;
}

void TrainBackground::Init()
{

    train.Init(TRAIN_START_POS, NUM_TRAMS, scrollRate);
    pos = Vector2D(0, TRAIN_HEIGHT);
    stationPosX = 4000;
    tracksPosX = 0;
    tempT = load_image("sprites/backgrounds/track.png");
    station = load_image("sprites/backgrounds/station.png");

    SDL_DisplayFormatAlpha(tempT);

    tracks = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, 120 * tempT->w, tempT->h, tempT->format->BitsPerPixel, tempT->format->Gmask, tempT->format->Gmask, tempT->format->Gmask, 255);
    for (unsigned int i = 0; i < 120; ++i)
        apply_surface(Vector2D(tempT->w * i, 0), tempT, tracks);




}
void TrainBackground::Update(CGameEngine *game, Vector2D p)
{
    if ((p.x) * scrollRate - (tracksPosX + tracks->w) > 100)
        tracksPosX += tracks->w;
    if ((p.x) * scrollRate - (stationPosX + station->w) > 100)
        stationPosX += RandDouble(2500, 5000);

    train.Update(game, p);
}

Vector2D ScaleX(Vector2D pos, Vector2D p, double sr)
{
    return Vector2D((pos.x) - p.x * sr, pos.y);
}

void TrainBackground::Draw(CGameEngine *game, Vector2D p)
{
    Vector2D tracksdraw = ScaleX(Vector2D(tracksPosX, pos.y), p, scrollRate);
    Vector2D stationdraw = ScaleX(Vector2D(stationPosX, pos.y), p, scrollRate);

    apply_surface(tracksdraw, tracks, game->GetScreen());
    apply_surface(Vector2D(tracksdraw.x + tracks->w, pos.y), tracks, game->GetScreen());


    train.Draw(game, p);

    apply_surface(stationdraw, station, game->GetScreen());
}
void TrainBackground::Cleanup()
{
    SDL_FreeSurface(tempT);
    SDL_FreeSurface(tracks);
    SDL_FreeSurface(station);
    train.Cleanup();
}
