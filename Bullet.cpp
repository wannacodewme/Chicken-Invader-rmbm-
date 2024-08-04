#include<Bullet.h>

Bullet::Bullet()
{
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = BLASTER;
}

Bullet::~Bullet()
{

}

void Bullet::LoadImgBullet(SDL_Renderer* screen, int bullet_level)
{
    if (bullet_type_ == BLASTER)
    {
        std::string blaster_str = "image/blaster" + std::to_string(bullet_level) + ".png";
        LoadImg(blaster_str, screen);       
    }
    else if (bullet_type_ == NEUTRON)
    {
        std::string neutron_str = "image/neutron" + std::to_string(bullet_level) + ".png";
        LoadImg(neutron_str, screen);
    }
    else if (bullet_type_ == BORON) {
        std::string boron_str = "image/boron" + std::to_string(bullet_level) + ".png";
        LoadImg(boron_str, screen);
    }
}

void Bullet::HandleMove()
{
    if (is_move_)
    {
        rect_.y -= y_val_;
        if (rect_.y < -rect_.h)
        {
            is_move_ = false;
        }
    }    
}