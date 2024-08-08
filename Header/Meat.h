#ifndef MEAT_H_INCLUDED
#define MEAT_H_INCLUDED

#include<BaseObject.h>

#define MEAT_WIDTH 30
#define MEAT_HEIGHT 42
#define MEAT_SPEED 2

class Meat : public BaseObject
{
public:
	Meat();
	~Meat();

	void HandleMove();

	void SetXVal(const int& xVal) { x_val_ = xVal; }
	void SetYVal(const int& yVal) { y_val_ = yVal; }
	int GetXVal()const { return x_val_; }
	int GetYVal()const { return y_val_; }
	void SetIsMove(const bool& isMove) { is_move_ = isMove; }
	bool GetIsMove()const { return is_move_; }

private:
	int x_val_;
	int y_val_;
	bool is_move_;
};

#endif // !MEAT_H_INCLUDED