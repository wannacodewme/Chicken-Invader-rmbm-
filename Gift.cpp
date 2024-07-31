#include<Gift.h>
#include<Bullet.h>

Gift::Gift()
{
	type_ = Bullet::BLASTER;
	x_val_ = 0;
	y_val_ = GIFT_SPEED;
	rect_.x = rand() % (SCREEN_WIDTH - GIFT_WIDTH);
	rect_.y = 0;
	frame_ = LEVEL_UP_NUMBER_FRAME * 3;
	is_move_ = true;
	SetClip();
}

Gift::~Gift()
{

}

SDL_Rect Gift::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = LEVEL_UP_WIDTH;
	rect.h = LEVEL_UP_HEIGHT;

	return rect;
}

void Gift::SetClip()
{
	for (int i = 0; i < LEVEL_UP_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * LEVEL_UP_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = LEVEL_UP_WIDTH;
		clip_[i].h = LEVEL_UP_HEIGHT;
	}
}

void Gift::HandleMove()
{
	if (is_move_)
	{
		rect_.y += y_val_;
		if (rect_.y > SCREEN_HEIGHT + GIFT_HEIGHT)
		{
			is_move_ = false;
		}
	}
	
}

void Gift::LoadImgGift(SDL_Renderer* screen)
{
	std::string str_gift = "image/gift" + std::to_string(type_) + ".png";
	LoadImg(str_gift, screen);
}

void Gift::Show(SDL_Renderer* screen)
{
	if (type_ == 3)
	{
		frame_++;
		if (frame_ / 3 >= 25)
			frame_ = 0;
		SDL_Rect renderquad = { rect_.x, rect_.y, LEVEL_UP_WIDTH, LEVEL_UP_HEIGHT };
		SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 3], &renderquad);
	}
	else if(type_ < 3)
	{
		Render(screen);
	}
}