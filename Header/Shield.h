#ifndef SHIELD_H
#define SHIELD_H

#include<BaseObject.h>

class Shield : public BaseObject
{
public:
	Shield();
	~Shield();
	void Show(SDL_Renderer* screen);

private:
	double spin_angle_;
};

#endif // !SHIELD_H