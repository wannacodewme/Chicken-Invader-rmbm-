#include<BaseObject.h>

BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free();
    p_object_ = LoadImage(path, screen, rect_.w, rect_.h);
    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* screen, const SDL_Rect* clip)
{
    SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
    SDL_RenderCopy(screen, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}