#include "MoveObject.h"

MoveObject::MoveObject()
{
    dino = new Dino(sheet, 1.5);
    threat = new Threat();
}

MoveObject::~MoveObject()
{
    delete dino;
    delete threat;
}
void MoveObject::update()
{
    dino->update();
    threat->update();
}
void MoveObject::render(SDL_Renderer *renderer)
{
    dino->render(renderer, dino->getRect());
    threat->render(renderer);
}
void MoveObject::handleDinoEvent()
{
    dino->jump(event);
    dino->duck(event);
}
bool MoveObject::isCollide()
{
    return threat->isCollide(dino->hitBox);
}
void MoveObject::setDinoDied()
{
    if (isCollide())
        dino->setDied();
}
void MoveObject::reset()
{
    dino->reset();
    threat->reset();
}

void MoveObject::initRandom()
{
    int a = Random::random(1, 2);
    if (a == 1)
    {
        threat->increaseCactus();
    }
    else
    {
        threat->increasePtero();
    }
}
void MoveObject::upLevel()
{
    threat->getPteroNum() == 1 ? threat->increaseCactus() : initRandom();
}
void MoveObject::resetLevel()
{
    if (threat->getNum() > 3)
    {
        threat->setDefault();
    }

}
