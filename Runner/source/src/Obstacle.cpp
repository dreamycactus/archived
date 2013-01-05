#include "../include/Obstacle.h"


//
//Obstacle::Obstacle(Vector2D pos, Vector2D box) : Thing(pos, box)
//{
    //this->type = type;
    //state = O_DYING;
    //alpha = 255;
    //frame = 0;
    //sprite_sheet = load_image("sprites/box.png");

//}

//void Obstacle::Update(CGameEngine *game, Runner *player)
//{
//    if (state == O_DYING)
//    {
//        alpha = max(alpha - ALPHA_DECAY, 0);
//        SDL_SetAlpha( sprite_sheet, SDL_SRCALPHA, alpha );
//    }
//    if (alpha == 0)
//        state = O_DEAD;
//
//}
//
//void Obstacle::Draw(CGameEngine *game, Runner *player)
//{
//    apply_surface(pos - player->GetPosX() + START_POS, sprite_sheet, game->GetScreen());
//}


//int Obstacle::GetType()
//{
//    return type;
//}
//
//int Obstacle::GetState()
//{
//    return state;
//}
//
//void Obstacle::SetState(int state)
//{
//    this->state = state;
//}
//
//void Obstacle::Cleanup()
//{
//    SDL_FreeSurface(sprite_sheet);
//
//}
