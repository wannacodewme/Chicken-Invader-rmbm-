#include<Egg.h>

Egg::Egg()
{
    x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}

Egg::~Egg()
{

}

void Egg::HandleMove(SDL_Renderer* screen)
{
    if (is_move_)
    {
        rect_.y += EGG_SPEED;
        if (rect_.y >= SCREEN_HEIGHT - rect_.w)
        {
            is_move_ = false;
        }
    }   
}

void Egg::HandleMoveBoss(SDL_Renderer* screen)
{
    if (is_move_)
    {
        rect_.y += EGG_BOSS_SPEED;
        if (rect_.y >= SCREEN_HEIGHT)
        {
            is_move_ = false;
        }
    }
}