#include<Shield.h>

Shield::Shield()
{
	spin_angle_ = 0;
}

Shield::~Shield()
{

}

void Shield::Show(SDL_Renderer* screen)
{
	spin_angle_ += 5;
	if (spin_angle_ > 360)
	{
		spin_angle_ = 0;
	}
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopyEx(screen, p_object_, NULL, &renderquad, spin_angle_, NULL, SDL_FLIP_NONE);
}