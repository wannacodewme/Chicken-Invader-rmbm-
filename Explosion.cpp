#include<Explosion.h>

Explosion::Explosion()
{
    frame_ = EXPLOSION_NUMBER_FRAME * 2;
    SetClip();
}

Explosion::~Explosion()
{

}

void Explosion::SetClip()
{
    for (int i = 0; i < EXPLOSION_NUMBER_FRAME; i++)
    {
        clip_[i].x = i * EXPLOSION_WIDTH;
        clip_[i].y = 0;
        clip_[i].w = EXPLOSION_HEIGHT;
        clip_[i].h = EXPLOSION_HEIGHT;
    }
}

void Explosion::Show(SDL_Renderer* screen)
{
    frame_++;
    SDL_Rect renderQuad = { rect_.x, rect_.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT };
    SDL_RenderCopy(screen, p_object_, &clip_[frame_ / 2], &renderQuad);
}