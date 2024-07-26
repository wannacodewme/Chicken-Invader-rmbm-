#ifndef MENU_H
#define MENU_H

#include "../Button/Button.h"
#include "../Text/Text.h"

class Menu
{
private:
    Texture *bg;

public:
    Menu();
    ~Menu();

    Button *play;
    Button *exit;

    Text *info;
    SDL_Rect info_r = {0, 0, 120, 60};
    Vector info_p = {SCREEN_WIDTH - 110, SCREEN_HEIGHT - 50};
    Button *INFO;
    
    void render(SDL_Renderer *renderer);
    void update();
};

#endif