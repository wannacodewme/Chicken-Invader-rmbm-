#include<Boss.h>

Boss::Boss()
{
	rect_.x = 0;
	rect_.y = 40;
	x_val_ = BOSS_SPEED;
	y_val_ = BOSS_SPEED;
	x_limit_left_ = 0;
	x_limit_right_ = SCREEN_WIDTH - BOSS_WIDTH;
	y_limit_top_ = 30;
	y_limit_under_ = 260;
	frame_ = 0;
	heart_ = BOSS_HEART;
	status_.right_ = 1;
	status_.left_ = 0;
	status_.down_ = 1;
	status_.up_ = 0;
	last_time_shoot = -1500;
	SetClip();
}

Boss::~Boss()
{

}

void Boss::SetClip()
{
	for (int i = 0; i < BOSS_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * BOSS_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = BOSS_WIDTH;
		clip_[i].h = BOSS_HEIGHT;
	}
}

SDL_Rect Boss::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = BOSS_WIDTH;
	rect.h = BOSS_HEIGHT;
	return rect;
}

void Boss::Show(SDL_Renderer* screen)
{
	if (heart_ > 0)
	{
		frame_++;
		if (frame_ / 5 >= BOSS_NUMBER_FRAME)
		{
			frame_ = 0;
		}
		SDL_Rect renderQuad = { rect_.x, rect_.y, BOSS_WIDTH, BOSS_HEIGHT };
		SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 5], &renderQuad);
	}
}

void Boss::HandleMove()
{
	if (heart_ > 0)
	{		
		if (status_.left_)
		{
			rect_.x -= x_val_;
		}
		else if (status_.right_)
		{
			rect_.x += x_val_;
		}
		if (status_.down_)
		{
			rect_.y += y_val_;
		}
		else if (status_.up_)
		{
			rect_.y -= y_val_;
		}

		if (rect_.x >= x_limit_right_)
		{
			status_.left_ = 1;
			status_.right_ = 0;
			x_limit_right_ = (rand() % 451) + 550;
		}
		else if (rect_.x <= x_limit_left_)
		{
			status_.left_ = 0;
			status_.right_ = 1;
			x_limit_left_ = (rand() % 451);
		}
		if (rect_.y <= y_limit_top_)
		{
			status_.up_ = 0;
			status_.down_ = 1;
			y_limit_top_ = (rand() % 91) + 30;
		}
		else if (rect_.y >= y_limit_under_)
		{
			status_.up_ = 1;
			status_.down_ = 0;
			y_limit_under_ = (rand() % 91) + 170;
		}		
	}
}

void Boss::InitEgg(Egg* p_egg, SDL_Renderer* screen)
{
	if (p_egg)
	{
		p_egg->LoadImg("image/eggboss.png", screen);
		p_egg->SetIsMove(true);
		p_egg->SetRect(this->rect_.x + BOSS_WIDTH / 2 - p_egg->GetRect().w / 2, this->rect_.y + BOSS_HEIGHT - 10);
		p_egg->SetYVal(EGG_BOSS_SPEED);
		p_egg_list_.push_back(p_egg);
	}
}

void Boss::MakeEgg(SDL_Renderer* screen)
{
	if (SDL_GetTicks() - last_time_shoot > 800)
	{
		last_time_shoot = SDL_GetTicks();

		Egg* p_egg = new Egg;
		InitEgg(p_egg, screen);
	}

	for (int i = 0; i < p_egg_list_.size(); i++)
	{
		Egg* p_egg = p_egg_list_.at(i);
		if (p_egg)
		{
			if (p_egg->GetIsMove())
			{
				p_egg->Render(screen);
				p_egg->HandleMoveBoss(screen);
			}
			else
			{
				RemoveEgg(i);
				i--;
			}
		}
	}
}

void Boss::RemoveEgg(const int& idx)
{
	if (idx < p_egg_list_.size())
	{
		Egg* p_egg = p_egg_list_.at(idx);
		p_egg_list_.erase(p_egg_list_.begin() + idx);
		if (p_egg != NULL)
		{
			delete p_egg;
			p_egg = NULL;
		}
	}
}

void Boss::ShowHeart(SDL_Renderer* screen, int w, int h)
{
	SDL_Rect fill_rect;
	fill_rect.x = rect_.x + 50;
	fill_rect.y = rect_.y - h - 5;
	fill_rect.w = w;
	fill_rect.h = h;
	SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
	SDL_RenderFillRect(screen, &fill_rect);
}