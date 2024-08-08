#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include<BaseObject.h>

#define BLASTER_SPEED 12
#define NEUTRON_SPEED 18
#define BORON_SPEED 30

class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet();

    enum BulletType
    {
        BLASTER = 0,
        NEUTRON = 1,
        BORON = 2,
    };

    void SetXVal(const int& xVal) { x_val_ = xVal; }
    void SetYVal(const int& yVal) { y_val_ = yVal; }
    int GetXVal()const { return x_val_; }
    int GetYVal()const { return y_val_; }
    void SetIsMove(const bool& isMove) { is_move_ = isMove; }
    bool GetIsMove()const { return is_move_; }
    void SetType(const int& bulletType) { bullet_type_ = bulletType; }
    int GetType()const { return bullet_type_; }

    void HandleMove();
    void LoadImgBullet(SDL_Renderer* screen, int bullet_level);
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int bullet_type_;
};

#endif