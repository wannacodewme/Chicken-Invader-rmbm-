#include<Menu.h>

Menu::Menu()
{
    menu_number = 0;
}

Menu::~Menu()
{

}

bool Menu::CheckMouseVsItem(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

bool Menu::ShowMenu(SDL_Event& e,const std::string& s, SDL_Renderer* screen, TTF_Font* font_menu, Mix_Music* music_start, Mix_Chunk* sound_button)
{
    bool ret = menu.LoadImg("image/menugame.png", screen);
    if (!ret)
        return false;
    ret = menu2.LoadImg("image/guidance.png", screen);
    if (!ret)
        return false;

    const int number_of_item = 3;
    SDL_Rect pos_arr[number_of_item];
    Text text_menu[number_of_item];

    text_menu[0].SetText(s);
    text_menu[0].SetColor(Text::BLACK);
    text_menu[0].ShowText(font_menu, screen);
    pos_arr[0].x = SCREEN_WIDTH / 2 - text_menu[0].GetRect().w / 2;
    pos_arr[0].y = SCREEN_HEIGHT - 300;
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("Tutorial");
    text_menu[1].SetColor(Text::BLACK);
    text_menu[1].ShowText(font_menu, screen);
    pos_arr[1].x = SCREEN_WIDTH / 2 - text_menu[1].GetRect().w / 2;
    pos_arr[1].y = SCREEN_HEIGHT - 200;
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].SetText("Quit");
    text_menu[2].SetColor(Text::BLACK);
    text_menu[2].ShowText(font_menu, screen);
    pos_arr[2].x = SCREEN_WIDTH / 2 - text_menu[2].GetRect().w / 2;
    pos_arr[2].y = SCREEN_HEIGHT - 100;
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

    int xm = 0, ym = 0;
    Mix_PlayMusic(music_start, -1);
    bool isRunning = true;
    bool quit = false;
    while (!quit)
    {        
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                return false;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                xm = e.motion.x;
                ym = e.motion.y;

                for (int i = 0; i < number_of_item; i++)
                {
                    if (CheckMouseVsItem(xm, ym, text_menu[i].GetRect()))
                        text_menu[i].SetColor(Text::WHITE);
                    else
                        text_menu[i].SetColor(Text::BLACK);
                }                
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                xm = e.button.x;
                ym = e.button.y;
                if (menu_number == 0)
                {
                    for (int i = 0; i < number_of_item; i++)
                    {
                        if (CheckMouseVsItem(xm, ym, text_menu[i].GetRect()))
                        {
                            if (i == 0)
                            {
                                quit = true;                                
                                isRunning = true;
                            }
                            else if (i == 1)
                            {
                                menu_number = 1;                               
                            }
                            else if (i == 2)
                            {
                                quit = true;
                                return false;
                            }
                            Mix_PlayChannel(-1, sound_button, 0);
                        }
                    }
                }
                else if (menu_number == 1)
                {
                    Mix_PlayChannel(-1, sound_button, 0);
                    menu_number = 0;
                }
            }
        }
        if (menu_number == 0)
        {
            menu.Render(screen);
            for (int i = 0; i < number_of_item; i++)
            {
                text_menu[i].ShowText(font_menu, screen);
            }
        }
        else if (menu_number == 1)
        {
            menu2.Render(screen);
        }
        SDL_RenderPresent(screen);
    }
    Mix_PauseMusic();
    return isRunning;
}