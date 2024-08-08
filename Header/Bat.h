#ifndef BAT_H_INCLUDED
#define BAT_H_INCLUDED

#include<BaseObject.h>
#include<Egg.h>
#include<EggBreak.h>

#define BAT_WIDTH 63
#define BAT_HEIGHT 58
#define BAT_NUMBER_FRAME 5
#define BAT_SPEED 3

class Bat : public BaseObject
{
public:
	Bat();
	~Bat();

	void HandleMove(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void SetClip();
	SDL_Rect GetRectFrame();

	void SetXVal(const int& val) { x_val_ = val; }
	void SetYVal(const int& val) { y_val_ = val; }
	int GetXVal() const { return x_val_; }
	int GetYVal() const { return y_val_; }

	void SetAlive(const bool& live) { alive_ = live; }
	bool GetAlive() const { return alive_; }
	void SetFrame(const int& frame) { frame_ = frame; }
	int GetFrame()const { return frame_; }

	void SetEggList(std::vector<Egg*> egg_list) { p_egg_list_ = egg_list; }
	std::vector<Egg*> GetEggList() const { return p_egg_list_; }
	void InitEgg(Egg* p_egg, SDL_Renderer* screen);
	void MakeEgg(SDL_Renderer* screen);
	void RemoveEgg(const int& idx);

	void ShowEggBreak(SDL_Renderer* screen);
	std::vector<EggBreak*> GetEggBreakList() const { return p_eggbreak_list_; }

private:
	int x_val_;
	int y_val_;
	int y_limit_;

	int frame_;
	SDL_Rect clip_[BAT_NUMBER_FRAME];
	bool alive_;

	std::vector<Egg*> p_egg_list_;
	std::vector<EggBreak*> p_eggbreak_list_;
};

#endif // !BAT_H_INCLUDED