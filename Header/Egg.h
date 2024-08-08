#ifndef EGG_H_INCLUDED
#define EGG_H_INCLUDED

#include<BaseObject.h>

#define EGG_WIDTH 23
#define EGG_HEIGHT 31
#define EGG_SPEED 3
#define RED_EGG_WIDTH 11
#define RED_EGG_HEIGHT 15
#define EGG_BOSS_WIDTH 60
#define EGG_BOSS_HEIGHT 80
#define EGG_BOSS_SPEED 9

class Egg : public BaseObject
{
public:
	Egg();
	~Egg();	

	void SetXVal(const int& xVal) { x_val_ = xVal; }
	void SetYVal(const int& yVal) { y_val_ = yVal; }
	void SetIsMove(const bool& isMove) { is_move_ = isMove; }
	bool GetIsMove()const { return is_move_; }
	void HandleMove(SDL_Renderer* screen);
	void HandleMoveBoss(SDL_Renderer* screen);

private:
	int x_val_;
	int y_val_;
	bool is_move_;
};

#endif // !EGG_H_INCLUDED