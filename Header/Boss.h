#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include<BaseObject.h>
#include<Egg.h>

#define BOSS_WIDTH 200
#define BOSS_HEIGHT 117
#define BOSS_SPEED 4
#define BOSS_NUMBER_FRAME 10

class Boss : public BaseObject
{
public:
	Boss();
	~Boss();

    void HandleMove();
    void Show(SDL_Renderer* screen);
    void SetClip();
    SDL_Rect GetRectFrame();

    void SetXVal(const int& val) { x_val_ = val; }
    void SetYVal(const int& val) { y_val_ = val; }
    int GetXVal() const { return x_val_; }
    int GetYVal() const { return y_val_; }

    void SetHeart(const double& heart) { heart_ = heart; }
    void DecreaseHeart(const double& damage) { heart_ -= damage; }
    double GetHeart() const { return heart_; }

    void SetEggList(std::vector<Egg*> egg_list) { p_egg_list_ = egg_list; }
    std::vector<Egg*> GetEggList() const { return p_egg_list_; }
    void InitEgg(Egg* p_egg, SDL_Renderer* screen);
    void MakeEgg(SDL_Renderer* screen);
    void RemoveEgg(const int& idx);
    void ShowHeart(SDL_Renderer* screen, int w, int h);

private:
	int x_val_;
	int y_val_;
	double heart_;
    int frame_;
    int x_limit_left_; //0->450
    int x_limit_right_; // 550->1000
    int y_limit_top_; //30->120
    int y_limit_under_; //170 -> 260
    SDL_Rect clip_[BOSS_NUMBER_FRAME];
    StatusThreats status_;
    std::vector<Egg*> p_egg_list_;
    Uint32 last_time_shoot;
};

#endif