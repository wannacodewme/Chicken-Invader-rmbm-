#include "Background.h"

Background::Background()
{

    cloud = new Cloud(sheet);
    road = new Road(sheet);

    gameover = new Texture(sheet, 1);
    restartButton = new Texture(sheet, 1);

    pause = new Button(buttons.pause.path, &buttons.pause.rect, 1.5);
    pause->setPos({10, 10});

    music = new Button(buttons.musicSetting.path, &buttons.musicSetting.rect, 1.5);
    music->setPos({62, 10});

    color = {255, 255, 255, 255};
}
Background::~Background()
{
    delete cloud;
    delete road;
    delete gameover;
    delete restartButton;
    delete pause;
    delete music;
}

void Background::setNight()
{
    if (this->color.r > night.r)
    {
        this->color.r -= change;
    }
    if (this->color.g > night.g)
    {
        this->color.g -= change;
    }
    if (this->color.b > night.b)
    {
        this->color.b -= change;
    }
    if (this->color.r == night.r && this->color.g == night.g && this->color.b == night.b)
    {
        isNight = true;
    }
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderClear(renderer);
}
void Background::setDay()
{
    if (this->color.r < day.r)
    {
        this->color.r += change;
    }
    if (this->color.g < day.g)
    {
        this->color.g += change;
    }
    if (this->color.b < day.b)
    {
        this->color.b += change;
    }
    if (this->color.r == day.r && this->color.g == day.g && this->color.b == day.b)
    {
        isNight = false;
    }
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderClear(renderer);
}
void Background::setIsNight()
{
    isNight = true;
}
void Background::setIsDay()
{
    isNight = false;
}

void Background::update()
{

    cloud->update();
    road->update();

    pause->hover();
    music->hover();
}
void Background::renderEntity(SDL_Renderer *renderer)
{
    cloud->render(renderer, cloud->getRect());
    road->render(renderer, road->getRect());

    pause->render(renderer, pause->getRect());
    music->render(renderer, music->getRect());
}

void Background::renderBg(SDL_Renderer *renderer)
{

    if (!isNight)
    {
        setDay();
    }
    else if (isNight)
    {
        setNight();
    }
}

void Background::renderGameOver(SDL_Renderer *renderer)
{
    SDL_Rect gameover_r{1293, 27, 384, 24};
    Vector gameoverPos = {static_cast<int>((SCREEN_WIDTH - gameover_r.w) / 2), static_cast<int>((SCREEN_HEIGHT - gameover_r.h) / 2) - 100};
    gameover->renderWithPosAndScale(renderer, &gameover_r, gameoverPos, 1);

    SDL_Rect restartButton_r{2, 2, 72, 64};
    Vector restartButtonPos = {static_cast<int>(SCREEN_WIDTH - restartButton_r.w) / 2, static_cast<int>((SCREEN_HEIGHT - restartButton_r.h) / 2)};
    restartButton->renderWithPosAndScale(renderer, &restartButton_r, restartButtonPos, 1);
    
    pause->afterClick();
    music->afterClick();
}

void Background::reset()
{
    setIsDay();
    cloud->reset();
    road->reset();
}
void Background::pauseBg()
{
    pause->setRect(&buttons.pause.resume);
    pause->afterClick();
}
void Background::resumeBg()
{
    pause->setRect(&buttons.pause.rect);
    pause->afterClick();
}
