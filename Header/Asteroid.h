#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include<BaseObject.h>

#define ASTEROID_HEART 3

class Asteroid : public BaseObject
{
public:
	Asteroid();
	~Asteroid();

	void Show(SDL_Renderer* screen);
	void LoadImgAsteroid(SDL_Renderer* screen);
	void HandleMove();

	void SetXVal(const int& val) { x_val_ = val; }
	void SetYVal(const int& val) { y_val_ = val; }
	int GetXVal() const { return x_val_; }
	int GetYVal() const { return y_val_; }
	void SetWidthHeight(const double& scale);
	void DecreaseHeart() { heart_--; }
	int GetHeart() const { return heart_; }

private:
	int x_val_;
	int y_val_;
	int type_;
	int spin_angle_;
	int heart_;
};

#endif