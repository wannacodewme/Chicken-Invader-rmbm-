#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include<BaseObject.h>

#define EXPLOSION_WIDTH 150
#define EXPLOSION_HEIGHT 165
#define EXPLOSION_NUMBER_FRAME 8

class Explosion : public BaseObject
{
public:
	Explosion();
	~Explosion();

	void SetClip();
	void Show(SDL_Renderer* screen);
	void SetFrame(const int& frame) { frame_ = frame; }
	int GetFrame()const { return frame_; }

private:
	int frame_;
	SDL_Rect clip_[EXPLOSION_NUMBER_FRAME];
};

#endif // !EXPLOSION_H_INCLUDED