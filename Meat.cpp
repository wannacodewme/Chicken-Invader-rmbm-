#include<Meat.h>

Meat::Meat()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}

Meat::~Meat()
{

}

void Meat::HandleMove()
{
    if (is_move_)
    {
        rect_.y += MEAT_SPEED;
        if (rect_.y >= SCREEN_HEIGHT + MEAT_HEIGHT)
        {
            is_move_ = false;
        }
    }
}