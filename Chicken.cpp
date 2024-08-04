#include<Chicken.h>

Chicken::Chicken()
{
	x_val_ = 0;
	y_val_ = 0;
	alive_ = true;
	order_in_row_ = 0;
	frame_ = 0;
	status_.down_ = 0;
	status_.up_ = 0;
	status_.left_ = 0;
	status_.right_ = 0;
	heart_ = CHICKEN_HEART;
	last_time_shoot = -1000;
	SetClip();
}

Chicken::~Chicken()
{

}

void Chicken::SetClip()
{
	for (int i = 0; i < CHICKEN_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * CHICKEN_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = CHICKEN_WIDTH;
		clip_[i].h = CHICKEN_HEIGHT;
	}
}

SDL_Rect Chicken::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = CHICKEN_WIDTH;
	rect.h = CHICKEN_HEIGHT;
	return rect;
}

void Chicken::Show(SDL_Renderer* screen)
{
	if (alive_)
	{
		frame_++;
		if (frame_ / 5 >= CHICKEN_NUMBER_FRAME)
		{
			frame_ = 0;
		}
		SDL_Rect renderQuad = { rect_.x, rect_.y, CHICKEN_WIDTH, CHICKEN_HEIGHT };
		SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 5], &renderQuad);
	}
}

void Chicken::HandleMove()
{
	if (alive_)
	{
		if (status_.left_)
		{
			rect_.x += x_val_;
		}
		else if (status_.right_)
		{
			rect_.x -= x_val_;
		}
		if (rect_.x >= SCREEN_WIDTH - (NUMBER_CHICKEN_PER_ROW - order_in_row_ - 1) * DISTANCE_BETWEEN_PER_CHICKEN - CHICKEN_WIDTH)
		{
			status_.left_ = 0;
			status_.right_ = 1;

		}
		else if (rect_.x <= order_in_row_ * DISTANCE_BETWEEN_PER_CHICKEN)
		{
			status_.left_ = 1;
			status_.right_ = 0;
		}
	}
}

void Chicken::InitEgg(Egg* p_egg, SDL_Renderer* screen)
{
	if (p_egg)
	{
		p_egg->LoadImg("image/egg0.png", screen);
		p_egg->SetIsMove(true);
		p_egg->SetRect(this->rect_.x + CHICKEN_WIDTH / 2 - p_egg->GetRect().w / 2, this->rect_.y + CHICKEN_HEIGHT - 10);
		p_egg->SetYVal(EGG_SPEED);
		p_egg_list_.push_back(p_egg);
	}
}

void Chicken::MakeEgg(SDL_Renderer* screen)
{				
	/*
	if (rand() % 1000 == 0)
	{
		Egg* p_egg = new Egg;
		InitEgg(p_egg, screen);
	}				
	*/

	//Every 2 soconds, each chicken has 25% to shoot again
	if (SDL_GetTicks() - last_time_shoot > 2000)
	{
		last_time_shoot = SDL_GetTicks();
		if (rand() % 4 == 0)
		{
			Egg* p_egg = new Egg;
			InitEgg(p_egg, screen);
		}		
	}

	for (int i = 0; i < p_egg_list_.size(); i++)
	{
		Egg* p_egg = p_egg_list_.at(i);
		if (p_egg)
		{
			if (p_egg->GetIsMove())
			{				
				p_egg->Render(screen);
				p_egg->HandleMove(screen);
			}
			else
			{
				//Add eggbreak
				EggBreak* p_eggbreak = new EggBreak;
				bool ret = p_eggbreak->LoadImg("image/eggBreak.png", screen);
				if (!ret)
					return;
				p_eggbreak->SetFrame(0);
				p_eggbreak->SetRect(p_egg->GetRect().x, SCREEN_HEIGHT - EGG_BREAK_HEIGHT);
				p_eggbreak_list_.push_back(p_eggbreak);

				RemoveEgg(i);
				i--;
			}
		}
	}
}

void Chicken::RemoveEgg(const int& idx)
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

void Chicken::ShowEggBreak(SDL_Renderer* screen)
{
	for (int e = 0; e < p_eggbreak_list_.size(); e++)
	{
		EggBreak* p_egg_break = p_eggbreak_list_.at(e);
		if (p_egg_break->GetFrame() < EGG_BREAK_NUMBER_FRAME * 4)
		{
			p_egg_break->Show(screen);
		}
		else
		{
			p_eggbreak_list_.erase(p_eggbreak_list_.begin() + e);
			p_egg_break = NULL;
			delete p_egg_break;
			e--;
		}
	}
}