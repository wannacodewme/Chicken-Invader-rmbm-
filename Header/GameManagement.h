#ifndef GAMEMANAGEMENT_H_
#define GAMEMANAGEMENT_H_

#include<CommonFunction.h>
#include<MainObject.h>
#include<Chicken.h>
#include<Boss.h>
#include<Bat.h>
#include<Explosion.h>
#include<Text.h>
#include<Meat.h>
#include<Shield.h>
#include<Asteroid.h>
#include<Gift.h>
#include<Menu.h>

class GameManagement
{
public:
	GameManagement();
	~GameManagement();

	bool Init();
	bool LoadMedia();
	void Close();
	void GameLoop();

	void HandleBackground();
	void HandleSpaceship();
	void HandleChicken();
	void HandleBoss();
	void HandleBat();
	void HandleMeat();
	void HandleGift();
	void HandleAsteroid();
	void ResetGame();

private:
	bool isRunning;
	int current_level;
	SDL_Window* g_window;
	SDL_Renderer* g_screen;
	SDL_Event g_event;

	Mix_Chunk* g_sound_bullet[3];
	Mix_Chunk* g_sound_explosion;
	Mix_Chunk* g_sound_level_up;
	Mix_Chunk* g_sound_chicken_hit[3];
	Mix_Chunk* g_sound_food;
	Mix_Music* g_music_start;

	TTF_Font* g_font_text;
	TTF_Font* g_font_menu;
	TTF_Font* g_font_announce;

	MainObject spaceship;
	Shield shield;
	std::vector<Chicken*> p_chicken_list;
	std::vector<Meat*> p_meat_list;
	Boss boss;
	std::vector<Bat*> p_bat_list;
	Uint32 time_init_bat;

	std::vector<Asteroid*> p_asteroid_list;

	BaseObject background;
	BaseObject background2;
	int scrolling;
	BaseObject menu_win;
	BaseObject menu_lose;

	Explosion explosion;
	std::vector<Gift*> p_gift_list;

	BaseObject scoreboard;
	Text heart_text;
	Text bullet_level_text;
	Text score_text; //How many chicken thigh has been eaten
	int total_kill; //How many chicken has been killed
	int meat_score;
	Text text_annouce;
	Uint32 time_annouce;

	Menu menu;
};

#endif