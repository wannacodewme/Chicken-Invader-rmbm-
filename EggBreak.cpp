#include<EggBreak.h>

EggBreak::EggBreak()
{
	frame_ = EGG_BREAK_NUMBER_FRAME * 4;
	SetClip();
}

EggBreak::~EggBreak()
{

}

void EggBreak::SetClip()
{
	for (int i = 0; i < EGG_BREAK_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * EGG_BREAK_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = EGG_BREAK_WIDTH;
		clip_[i].h = EGG_BREAK_HEIGHT;
	}
}

void EggBreak::SetClipRedEgg()
{
	for (int i = 0; i < EGG_BREAK_NUMBER_FRAME; i++)
	{
		clip_[i].x = i * RED_EGG_BREAK_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = RED_EGG_BREAK_WIDTH;
		clip_[i].h = RED_EGG_BREAK_HEIGHT;
	}
}

void EggBreak::Show(SDL_Renderer* screen)
{
	frame_++;
	SDL_Rect renderQuad = { rect_.x, rect_.y, EGG_BREAK_WIDTH, EGG_BREAK_HEIGHT };
	SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 4], &renderQuad);
}

void EggBreak::ShowRedEgg(SDL_Renderer* screen)
{
	frame_++;
	SDL_Rect renderQuad = { rect_.x, rect_.y, RED_EGG_BREAK_WIDTH, RED_EGG_BREAK_HEIGHT };
	SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 4], &renderQuad);
}