#ifndef Text_H_H
#define Text_H_H

#include "HamChung.h"

class Text
{
public:
	Text();
	~Text();

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void free();

	void SetColor();
	void SetText(string text);
	void RenderText(SDL_Renderer* des, int xp, int yp); // show text

private:
	string stringS;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width_text;
	int height_text;
};

#endif // !Text_H_H

