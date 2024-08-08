#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include<CommonFunction.h>
#include<BaseObject.h>

class Text :public BaseObject
{
public:
	Text();
	~Text();

	enum TextColor
	{
		RED,
		WHITE,
		BLACK,
	};

	void SetText(const std::string& text) { text_ = text; }
	void SetColor(const int& type);
	void ShowText(TTF_Font* font, SDL_Renderer* screen);

private:
	std::string text_;
	SDL_Color text_color_;
};

#endif

