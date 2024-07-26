#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../Object/Cloud.h"
#include "../Object/Road.h"
#include "../Button/Button.h"
class Background
{
private:
    Cloud *cloud;
    Road *road;

    Texture *gameover;
    Texture *restartButton;

    SDL_Color color;
    SDL_Color night = {15, 15, 15, 255};
    SDL_Color day = {255, 255, 255, 255};
    bool isNight = false;
    const int change = 5;

public:
    Background();
    ~Background();
    
    Button *pause;
    Button *music;

    void update();
    void renderEntity(SDL_Renderer *renderer);

    void setIsNight();
    void setIsDay();
    void setNight();
    void setDay();

    void renderBg(SDL_Renderer *renderer);
    void renderGameOver(SDL_Renderer *renderer);
    void reset();

    void pauseBg();
    void resumeBg();
};

#endif