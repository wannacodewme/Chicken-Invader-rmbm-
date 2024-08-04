#include<Bat.h>

Bat::Bat()
{
	rect_.x = rand() % (SCREEN_WIDTH - BAT_WIDTH);
	rect_.y = -BAT_HEIGHT;
	x_val_ = 0;
	y_val_ = BAT_SPEED;
	y_limit_ = (rand() % 300) + 100;
	frame_ = BAT_NUMBER_FRAME * 5;
	alive_ = true;
	SetClip();
}

Bat::~Bat()
{

}

void Bat::SetClip()
{
	for (int i = 0; i < BAT_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * BAT_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = BAT_WIDTH;
		clip_[i].h = BAT_HEIGHT;
	}
}

SDL_Rect Bat::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = BAT_WIDTH;
	rect.h = BAT_HEIGHT;
	return rect;
}

void Bat::HandleMove(SDL_Renderer* screen)
{
	if (alive_)
	{
		rect_.y += y_val_;
		if (rect_.y >= y_limit_)
		{
			alive_ = false;
			frame_ = (BAT_NUMBER_FRAME - 1) * 5;
			Egg* p_egg = new Egg;
			InitEgg(p_egg, screen);
		}			
	}
}

void Bat::Show(SDL_Renderer* screen)
{
	if (alive_)
	{
		frame_++;
		if (frame_ / 5 >= (BAT_NUMBER_FRAME - 1))
		{
			frame_ = 0;
		}
		SDL_Rect renderQuad = { rect_.x, rect_.y, BAT_WIDTH, BAT_HEIGHT };
		SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 5], &renderQuad);
	}
	else
	{
		frame_++;		
		SDL_Rect renderQuad = { rect_.x, rect_.y, BAT_WIDTH, BAT_HEIGHT };
		SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 5], &renderQuad);
	}
}

void Bat::InitEgg(Egg* p_egg, SDL_Renderer* screen)
{
	if (p_egg)
	{
		p_egg->LoadImg("image/egg_1.png", screen);
		p_egg->SetIsMove(true);
		p_egg->SetRect(this->rect_.x + BAT_WIDTH / 2 - p_egg->GetRect().w / 2, this->rect_.y + BAT_HEIGHT - 10);
		p_egg->SetYVal(EGG_SPEED);
		p_egg_list_.push_back(p_egg);
	}
}

void Bat::MakeEgg(SDL_Renderer* screen)
{
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
				bool ret = p_eggbreak->LoadImg("image/eggBreak_1.png", screen);
				if (!ret)
					return;
				p_eggbreak->SetFrame(0);
				p_eggbreak->SetClipRedEgg();
				p_eggbreak->SetRect(p_egg->GetRect().x, SCREEN_HEIGHT - RED_EGG_BREAK_HEIGHT);
				p_eggbreak_list_.push_back(p_eggbreak);

				RemoveEgg(i);
				i--;
			}
		}
	}
}

void Bat::RemoveEgg(const int& idx)
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

void Bat::ShowEggBreak(SDL_Renderer* screen)
{
	for (int e = 0; e < p_eggbreak_list_.size(); e++)
	{
		EggBreak* p_egg_break = p_eggbreak_list_.at(e);
		if (p_egg_break->GetFrame() < EGG_BREAK_NUMBER_FRAME * 4)
		{
			p_egg_break->ShowRedEgg(screen);
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