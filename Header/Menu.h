#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include<BaseObject.h>
#include<Text.h>

class Menu
{
public:
	Menu();
	~Menu();

	bool CheckMouseVsItem(const int& x, const int& y, const SDL_Rect& rect);
	bool ShowMenu(SDL_Event& e, const std::string& s, SDL_Renderer* screen, TTF_Font* font_menu, Mix_Music* music_start, Mix_Chunk* sound_button);

private:
	BaseObject menu;
	BaseObject menu2;
	int menu_number;
};

#endif