#include "HamChung.h"
#include "NhanVat.h"

HamChung gBackground;
NhanVat bird;

bool initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

	gWindows = SDL_CreateWindow("GAME_SDL2_Passing_Obstacle", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, heigth,
		SDL_WINDOW_SHOWN);

	if (gWindows == NULL) return false;

	gScreen = SDL_CreateRenderer(gWindows, -1, SDL_RENDERER_ACCELERATED);

	if (gScreen == NULL) return true;

	SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);


	int imgFlags = IMG_INIT_PNG;
	//cout << IMG_Init(imgFlags) << " " << imgFlags;
	if (!(IMG_Init(imgFlags) && imgFlags)) return false;

	return true;
}

void close()
{
	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;

	SDL_DestroyWindow(gWindows);
	gWindows = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	bool isQuit = false;

	if (initialize() == false) return -1;

	gBackground.setRect(0, 0);
	gBackground.LoadAnh("bg4.png", gScreen);

	bird.setRect(200, 200);
	bird.LoadAnh("angrybird.png", gScreen);


	while (!isQuit)
	{
		while (SDL_PollEvent(&gEvent))
		{
			if (gEvent.type == SDL_QUIT || gEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				isQuit = true;
				break;
			}

			bird.NhapPhimDiChuyen(gEvent);
		}

		SDL_RenderClear(gScreen);

		//background
		gBackground.Render(gScreen);

		//update liên tục hình ảnh bird
		bird.Dichuyen();
		bird.Render(gScreen);

		// hiện thị lên màn hình
		SDL_RenderPresent(gScreen);
	}

	bird.free();
	close();
	return 0;
}