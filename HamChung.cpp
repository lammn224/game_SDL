#include "HamChung.h"

HamChung::HamChung()
{
	object = NULL;
	vitri.x = 0;
	vitri.y = 0;
	vitri.w = 0;
	vitri.h = 0;
}
HamChung::~HamChung()
{
	free();
}

bool HamChung::LoadAnh(string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());

	if (load_surface != NULL)
	{
		// xóa phông trắng 
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 255, 255));

		// lưu hình ảnh vào texture
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);

		if (new_texture != NULL)
		{
			// gán thông số pixel
			vitri.w = load_surface->w;
			vitri.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	object = new_texture;
	if (object == NULL) return false;
	return true;
}

// hàm update hình ảnh lên màn hình
void HamChung::Render(SDL_Renderer * des)
{
	SDL_RenderCopy(des, object, NULL, &vitri);			//copy ảnh vừa load vào màn hình
}

void HamChung::free()
{
	if (object != NULL)
	{
		SDL_DestroyTexture(object);
		object = NULL;
		vitri.w = 0;
		vitri.h = 0;
	}
}

