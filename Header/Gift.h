#ifndef GIFT_H_INCLUDED
#define GIFT_H_INCLUDED

#include<BaseObject.h>

#define GIFT_WIDTH 49
#define GIFT_HEIGHT 58
#define LEVEL_UP_WIDTH 49
#define LEVEL_UP_HEIGHT 41
#define GIFT_SPEED 2
#define LEVEL_UP_NUMBER_FRAME 25

class Gift : public BaseObject
{
public:
	Gift();
	~Gift();

	void SetClip();
	void Show(SDL_Renderer* screen);
	void HandleMove();
	void LoadImgGift(SDL_Renderer* screen);
	SDL_Rect GetRectFrame();
	int GetType()const { return type_; }	
	void SetType(const int& type) { type_ = type; }
	void SetIsMove(const bool& move) { is_move_ = move; }
	bool GetIsMove()const { return is_move_; }

private:
	int x_val_;
	int y_val_;
	int type_;
	bool is_move_;
	int frame_;
	SDL_Rect clip_[LEVEL_UP_NUMBER_FRAME];
};

#endif // !GIFT_H_INCLUDED