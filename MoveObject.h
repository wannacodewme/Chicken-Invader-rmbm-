#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include "../Object/Cactus.h"
#include "../Object/Ptero.h"
#include "../Object/Dino.h"
#include "../Object/Threat.h"

class MoveObject
{
private:
    Dino *dino;

    Threat *threat;

public:
    MoveObject();
    ~MoveObject();

    void update();
    void render(SDL_Renderer *renderer);
    void handleDinoEvent();
    bool isCollide();
    void setDinoDied();
    void reset();
    void upLevel();
    void initRandom();
    void resetLevel();
};

#endif