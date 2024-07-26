#include "Menu.h"

Menu::Menu()
{
    play = new Button(buttons.play.path, &buttons.play.rect, 1.5);
    play->setPos({SCREEN_WIDTH - play->getRectWidth() - 10, SCREEN_HEIGHT - play->getRectHeight() - 135});

    exit = new Button(buttons.exit_.path, &buttons.exit_.rect, 1.5);
    exit->setPos({SCREEN_WIDTH - exit->getRectWidth() - 10, SCREEN_HEIGHT - exit->getRectHeight() - 30});

    bg = new Texture("res/img/background.png");

    info = new Text("INFO", &info_r, info_p);
    SDL_Texture *info_t = info->getTexture();
    INFO = new Button(info_t, &info_r, info_p);

}
Menu::~Menu()
{
    delete bg;
    delete play;
    delete exit;

}

void Menu::render(SDL_Renderer *renderer)
{
    SDL_Rect bg_{0, 0, 800, 400};
    SDL_Rect dest{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, bg->getTexture(), &bg_, &dest);

    play->render(renderer, play->getRect());
    exit->render(renderer, exit->getRect());
    INFO->render(renderer, INFO->getRect());
}
void Menu::update()
{
    play->hover();
    exit->hover();
}