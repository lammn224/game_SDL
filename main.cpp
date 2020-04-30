#include "HamChung.h"
#include "NhanVat.h"
#include "VatCan.h"
#include <ctime>
HamChung gBackground;
NhanVat bird;
VatCan* obstacle = new VatCan[soVatcan];

bool initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

	gWindows = SDL_CreateWindow("GAME_SDL2_Passing_Obstacle", 
								SDL_WINDOWPOS_UNDEFINED,
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


	for (int i = 0; i < soVatcan; i++)
	{
		VatCan* vatcan = obstacle + i;
		srand((int)time(0));
		int random_y = rand() % 400;			// khởi tạo giá trị ngẫu nhiên vị trí trên màn hình cho mỗi vật cản

		if (random_y > heigth - 100) random_y = heigth * 0.3;		// nếu random lớn hơn chiều cao thì mặc định giá trị này

		// gán vị trí ban đầu của mỗi vật cản
		vatcan->setRect(width + i * 300, random_y);

		vatcan->LoadAnh("pig.png", gScreen);		// load ảnh vật cản
		//vatcan->render(gscreen);

		// gán tốc độ di chuyển của vật cản
		vatcan->setX_value(1);
	}

	int startTime = SDL_GetTicks();

	while (!isQuit)
	{
		cout << "starTime = " << startTime << endl;
		//cout << "	i = " << i << endl;

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

		for (int i = 0; i <soVatcan; i++)
		{
			VatCan* vatcan = (obstacle + i);

			// update liên tục hình ảnh quái vật
			vatcan->DichuyenM();
			vatcan->Render(gScreen);
		}

		if (startTime < 1000) startTime = SDL_GetTicks();
		if (startTime >= 1000)
		{
			bird.Dichuyen();
			bird.Render(gScreen);
			startTime = SDL_GetTicks();
			//cout << "	new i = " << i << endl;
			cout << "			new time: " << startTime << endl;
		}

		// hiển thị lên màn hình
		SDL_RenderPresent(gScreen);
	}

	bird.free();
	gBackground.free();
	close();
	return 0;
}