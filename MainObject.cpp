#include<MainObject.h>

MainObject::MainObject()
{
	p_object_ = NULL;
	rect_.x = SCREEN_WIDTH / 2;
	rect_.y = SCREEN_HEIGHT / 2;
	rect_.w = MAIN_WIDTH;
	rect_.h = MAIN_HEIGHT;
	alive_ = true;
	frame_ = 0;
	bullet_type_ = Bullet::BLASTER;
	bullet_level_ = 0;
	heart_ = MAIN_HEART;
	bullet_damage_ = 0;
	is_protected_ = false;
	time_protected = 0;
	SetClip();
}

MainObject::~MainObject()
{

}

void MainObject::SetClip()
{
	for (int i = 0; i < MAIN_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * MAIN_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = MAIN_WIDTH;
		clip_[i].h = MAIN_HEIGHT;
	}
}

SDL_Rect MainObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = MAIN_WIDTH;
	rect.h = MAIN_HEIGHT - 10;
	return rect;
}

void MainObject::Show(SDL_Renderer* screen)
{
	if (alive_)
	{
		frame_++;
		if (frame_ / 4 >= MAIN_NUMBER_FRAME)
			frame_ = 0;
		SDL_Rect renderQuad = { rect_.x, rect_.y, MAIN_WIDTH, MAIN_HEIGHT };
		SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 4], &renderQuad);
	}
}

void MainObject::HandleEvent(SDL_Event e, SDL_Renderer* screen, Mix_Chunk* sound_bullet[], Mix_Chunk* sound_level_up)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		if (alive_)
		{
			rect_.x = e.motion.x - MAIN_WIDTH / 2;
			rect_.y = e.motion.y - MAIN_HEIGHT / 2;
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			if (alive_)
			{
				Bullet* p_bullet = new Bullet;				
				p_bullet->SetType(bullet_type_);
				if (p_bullet->GetType() == Bullet::BLASTER)
				{
					Mix_PlayChannel(-1, sound_bullet[0], 0);
					p_bullet->SetYVal(BLASTER_SPEED);
					bullet_damage_ = 1;
				}
				else if (p_bullet->GetType() == Bullet::NEUTRON)
				{
					Mix_PlayChannel(-1, sound_bullet[1], 0);
					p_bullet->SetYVal(NEUTRON_SPEED);
					bullet_damage_ = 1.5;
				}
				else if (p_bullet->GetType() == Bullet::BORON)
				{
					Mix_PlayChannel(-1, sound_bullet[2], 0);
					p_bullet->SetYVal(BORON_SPEED);
					bullet_damage_ = 2;
				}

				p_bullet->LoadImgBullet(screen, bullet_level_);
				p_bullet->SetRect(this->rect_.x + MAIN_WIDTH / 2 - p_bullet->GetRect().w / 2, this->rect_.y - p_bullet->GetRect().h + 5);
				p_bullet->SetIsMove(true);
				p_bullet_list_.push_back(p_bullet);
			}				
		}
	}
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_RETURN)
		{
			if (heart_ > 0 && alive_ == false)
			{
				Mix_PlayChannel(-1, sound_level_up, 0);
				is_protected_ = true;
				time_protected = SDL_GetTicks();
				alive_ = true;
			}
		}
	}
}

void MainObject::HandleMove()
{
	if (alive_)
	{
		if (rect_.x < 0)
		{
			rect_.x = 0;
		}
		else if (rect_.x + MAIN_WIDTH > SCREEN_WIDTH)
		{
			rect_.x = SCREEN_WIDTH - MAIN_WIDTH;
		}

		if (rect_.y < 0)
		{
			rect_.y = 0;
		}
		else if (rect_.y + MAIN_HEIGHT > SCREEN_HEIGHT + 20)
		{
			rect_.y = SCREEN_HEIGHT - MAIN_HEIGHT + 20;
		}
	}	
}

void MainObject::MakeBullet(SDL_Renderer* screen)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		Bullet* p_bullet_ = p_bullet_list_.at(i);
		if (p_bullet_ != NULL)
		{
			if (p_bullet_->GetIsMove())
			{
				p_bullet_->HandleMove();
				p_bullet_->Render(screen, NULL);
			}
			else
			{
				if (p_bullet_ != NULL)
				{
					p_bullet_list_.erase(p_bullet_list_.begin() + i);
					delete p_bullet_;
					p_bullet_ = NULL;
				}
			}
		}
	}
}

void MainObject::RemoveBullet(const int& idx)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		if (idx < p_bullet_list_.size())
		{
			Bullet* p_bullet = p_bullet_list_.at(idx);
			p_bullet_list_.erase(p_bullet_list_.begin() + idx);

			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}

void MainObject::IncreaseBulletLevel()
{
	bullet_level_++;
	if (bullet_level_ > 3)
		bullet_level_ = 3;
}

void MainObject::DecreaseBulletLevel()
{
	bullet_level_--;
	if (bullet_level_ < 0)
		bullet_level_ = 0;
}