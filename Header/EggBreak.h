#ifndef EGGBREAK_H_INCLUDED
#define EGGBREAK_H_INCLUDED

#include<BaseObject.h>

#define EGG_BREAK_NUMBER_FRAME 8
#define EGG_BREAK_WIDTH 28
#define EGG_BREAK_HEIGHT 24
#define RED_EGG_BREAK_WIDTH 23
#define RED_EGG_BREAK_HEIGHT 23

class EggBreak : public BaseObject
{
public:
	EggBreak();
	~EggBreak();

	void SetClip();
	void SetClipRedEgg();
	void Show(SDL_Renderer* screen);
	void ShowRedEgg(SDL_Renderer* screen);
	void SetFrame(const int& frame) { frame_ = frame; }
	int GetFrame()const { return frame_; }

private:
	int frame_;
	SDL_Rect clip_[EGG_BREAK_NUMBER_FRAME];
};


#endif