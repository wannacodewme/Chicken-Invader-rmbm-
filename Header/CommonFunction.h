#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include<iostream>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#define SHIELD_WIDTH 90
#define SHIELD_HEIGHT 89

const int BACKGROUND_WIDTH = 1200;
const int BACKGROUND_HEIGHT = 3840;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 760;
const int SCREEN_SPEED = 1;
const std::string WINDOW_TITLE = "Chicken Invaders";

const int NUMBER_OF_CHICKEN = 27;
const int NUMBER_OF_ASTEROID = 20;
const int NUMBER_CHICKEN_PER_ROW = 9;
const int DISTANCE_BETWEEN_PER_CHICKEN = 100;
const double CHICKEN_HEART = 3;
const double BOSS_HEART = 100;
const double BULLET_DAMAGE_LEVEL_UP = 0.5;
const int ONE_TURN_GIFT = 5;

struct StatusThreats
{
	int up_;
	int down_;
	int left_;
	int right_;
};


bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
SDL_Texture* LoadImage(std::string path, SDL_Renderer* screen, int& w, int& h);

#endif 