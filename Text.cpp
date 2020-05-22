#include "Text.h"

Text::Text()
{
}
Text::~Text()
{
	free();
}

bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, stringS.c_str(), text_color);
	if (text_surface)
	{
		texture = SDL_CreateTextureFromSurface(screen, text_surface);

		//lấy ra độ dài - rộng của text
		width_text = text_surface->w;
		height_text = text_surface->h;

		SDL_FreeSurface(text_surface);
	}
	if (texture == NULL) return false;

	return true;
}

void Text::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void Text::SetColor()
{
	SDL_Color Wcolor = { 255, 255, 255 };
	text_color = Wcolor;
}

void Text::SetText(string text)
{
	stringS = text;
}

void Text::RenderText(SDL_Renderer* des, int xp, int yp)
{
	SDL_Rect pos = { xp, yp, width_text, height_text }; // vi tri xuat hien tren man hinh

	SDL_RenderCopy(des, texture, NULL, &pos);
}