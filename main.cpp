#include <iostream>
#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

static SDL_Window* gWindows = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

const int width = 1200;			// chiều rộng màn hình
const int heigth = 600;			// chiều dài màn hình

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
	if (initialize() < 0) return -1;

	while (!isQuit)
	{
		while (SDL_PollEvent(&gEvent))
		{
			if (gEvent.type == SDL_QUIT || gEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				isQuit = true;
				break;
			}
		}
	}

	close();
	return 0;
}