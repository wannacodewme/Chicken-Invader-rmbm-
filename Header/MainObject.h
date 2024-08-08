#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include<CommonFunction.h>
#include<BaseObject.h>
#include<Bullet.h>

#define MAIN_WIDTH 60
#define MAIN_HEIGHT 81
#define MAIN_HEART 3
#define MAIN_NUMBER_FRAME 2

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    void SetClip();
    SDL_Rect GetRectFrame();
    void Show(SDL_Renderer* screen);
    void HandleEvent(SDL_Event e, SDL_Renderer* screen, Mix_Chunk* sound_bullet[], Mix_Chunk* sound_level_up);
    void HandleMove();
    
    void SetAlive(const bool& alive) { alive_ = alive; }
    bool GetAlive()const { return alive_; }
    void SetHeart(const int& heart) { heart_ = heart; }
    int GetHeart() const { return heart_; }
    void DecreaseHeart() { heart_--; }
    void SetIsProtected(const bool& protect) { is_protected_ = protect; }
    bool GetIsProtected() const { return is_protected_; }
    Uint32 GetTimeProtected() const { return time_protected; }

    void SetBulletList(std::vector<Bullet*> bullet_list) { p_bullet_list_ = bullet_list; }
    std::vector<Bullet*> GetBulletList() const { return p_bullet_list_; }
    void MakeBullet(SDL_Renderer* screen);
    void RemoveBullet(const int& idx);
    double GetBulletDamage()const { return bullet_damage_; }
    int GetBulletType()const { return bullet_type_; }
    void SetBulletType(const int& type) { bullet_type_ = type; }
    int GetBulletLevel() const { return bullet_level_; }
    void SetBulletLevel(const int& level) { bullet_level_ = level; }
    void IncreaseBulletLevel();
    void DecreaseBulletLevel();

private:
    bool alive_;
    int heart_;

    int frame_;
    SDL_Rect clip_[2];
    
    std::vector<Bullet*> p_bullet_list_;
    int bullet_type_;
    double bullet_damage_;
    int bullet_level_;
    
    bool is_protected_;
    Uint32 time_protected;
};

#endif

