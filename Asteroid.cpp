#include<Asteroid.h>

Asteroid::Asteroid()
{
	spin_angle_ = 0;
	x_val_ = rand() % 5 - 2;
	y_val_ = rand() % 5 + 2;
	type_ = 1 + rand() % 3;
	rect_.x = rand() % SCREEN_WIDTH;
	rect_.y = -100 - rand() % 500;
	heart_ = ASTEROID_HEART;
}

Asteroid::~Asteroid()
{

}

void Asteroid::SetWidthHeight(const double& scale)
{
	rect_.w = static_cast<int>(rect_.w * scale);
	rect_.h = static_cast<int>(rect_.h * scale);
}

void Asteroid::LoadImgAsteroid(SDL_Renderer* screen)
{	
	std::string path = "image/a" + std::to_string(type_) + ".png";
	LoadImg(path, screen);
}

void Asteroid::Show(SDL_Renderer* screen)
{
	if (heart_ > 0)
	{
		spin_angle_ += 8;
		if (spin_angle_ > 360)
		{
			spin_angle_ = 0;
		}
		SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
		SDL_RenderCopyEx(screen, p_object_, NULL, &renderquad, spin_angle_, NULL, SDL_FLIP_NONE);
	}	
}

void Asteroid::HandleMove()
{
	if (heart_ > 0)
	{
		rect_.x += x_val_;
		rect_.y += y_val_;
		if (rect_.y >= SCREEN_HEIGHT)
		{
			rect_.x = rand() % SCREEN_WIDTH;
			rect_.y = -100 - rand() % 45;
			x_val_ = rand() % 5 - 2;
			y_val_ = rand() % 5 + 2;
		}
	}
}