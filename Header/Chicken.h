#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include<BaseObject.h>
#include<Egg.h>
#include<EggBreak.h>

#define CHICKEN_WIDTH 75
#define CHICKEN_HEIGHT 68
#define CHICKEN_SPEED 1
#define CHICKEN_BULLET_SPEED 2
#define CHICKEN_NUMBER_FRAME 18

class Chicken : public BaseObject
{
public:
    Chicken();
    ~Chicken();

    void HandleMove();
    void Show(SDL_Renderer* screen);
    void SetClip();
    SDL_Rect GetRectFrame();

    void SetXVal(const int& val) { x_val_ = val; }
    void SetYVal(const int& val) { y_val_ = val; }
    int GetXVal() const { return x_val_; }
    int GetYVal() const { return y_val_; }

    void SetAlive(const bool& live) { alive_ = live; }
    bool GetAlive() const { return alive_; }
    void SetHeart(const double& heart) { heart_ = heart; }
    void DecreaseHeart(const double& damage) { heart_ -= damage; }
    double GetHeart() const { return heart_; }
    void SetStatusLeft() { status_.left_ = 1; }
    void SetStatusRight() { status_.right_ = 1; }
    void SetOrderInRow(const int& order) { order_in_row_ = order; }
    int GetOrderInRow() const { return order_in_row_; }

    void SetEggList(std::vector<Egg*> egg_list) { p_egg_list_ = egg_list; }
    std::vector<Egg*> GetEggList() const { return p_egg_list_; }
    void InitEgg(Egg* p_egg, SDL_Renderer* screen);
    void MakeEgg(SDL_Renderer* screen);
    void RemoveEgg(const int& idx);

    void ShowEggBreak(SDL_Renderer* screen);
private:
    int x_val_;
    int y_val_;

    SDL_Rect clip_[CHICKEN_NUMBER_FRAME];
    int frame_;
    int order_in_row_; //start with 0
    
    bool alive_;
    StatusThreats status_;
    double heart_;

    std::vector<Egg*> p_egg_list_;
    std::vector<EggBreak*> p_eggbreak_list_;
    Uint32 last_time_shoot;
};

#endif

