#include "HamChung.h"
#include "NhanVat.h"
#include "VatCan.h"
#include <ctime>
HamChung gBackground;
NhanVat bird;
VatCan* obstacle = new VatCan[soVatcan];
HamChung gIntro;
HamChung play;
HamChung exit_button;
Mix_Music* gMusic = NULL;
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gWin = NULL;

bool isLose(SDL_Rect nhanvat, SDL_Rect vatcan)
{
	int left_a = nhanvat.x;
	int right_a = nhanvat.x + nhanvat.w;
	int top_a = nhanvat.y;
	int bottom_a = nhanvat.y + nhanvat.h;

	int left_b = vatcan.x;
	int right_b = vatcan.x + vatcan.w;
	int top_b = vatcan.y;
	int bottom_b = vatcan.y + vatcan.h;

	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}

		else if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}

		else if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	return false;
}

bool isWin(SDL_Rect nhanvat)
{
	if (nhanvat.x >= width - 89) return true;
	return false;
}

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

	// khởi tạo IMG
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) && imgFlags)) return false;

	// khởi tạo audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) return false;

	return true;
}

void close()
{
	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;

	SDL_DestroyWindow(gWindows);
	gWindows = NULL;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (initialize() == false) return -1;

	gIntro.setRect(0, 0);
	gIntro.LoadAnh("intro.png", gScreen);

	play.setRect(500, 250);
	play.LoadAnh("PlayPixelArt.png", gScreen);

	exit_button.setRect(500, 400);
	exit_button.LoadAnh("ExitPixelArt.png", gScreen);

	gMusic = Mix_LoadMUS("main_theme.mp3");
	gScratch = Mix_LoadWAV("sfx_hit.wav");
	gWin = Mix_LoadWAV("sfx_end.wav");

	SDL_Event menuE;
	while (true)
	{
		gIntro.Render(gScreen);
		play.Render(gScreen);
		exit_button.Render(gScreen);

		//SDL_RenderClear(gScreen);
		SDL_RenderPresent(gScreen);

		while (SDL_PollEvent(&menuE))
		{
			switch (menuE.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (menuE.button.x >= 500 && menuE.button.x <= 700
					&& menuE.button.y >= 250 && menuE.button.y <= 350)
				{
					goto retry;
				}

				if (menuE.button.x >= 500 && menuE.button.x <= 700
					&& menuE.button.y >= 400 && menuE.button.y <= 500)
				{
					close();
					return 1;
				}
				break;

			case SDL_QUIT:
				close();
				return 0;
				break;
			}
		}

	}

	retry:
	bool isQuit = false;

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

			if (!Mix_PlayingMusic())
				Mix_PlayMusic(gMusic, -1);
			else if (Mix_PausedMusic())
				Mix_ResumeMusic();

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

			bool lose = isLose(bird.getRect(), vatcan->getRect());
			if (lose)
			{
				Mix_PlayChannel(-1, gScratch, 0);
				Mix_PauseMusic();
				int msBox = MessageBox(NULL, "====YOU LOSE====", "	====END GAME====", MB_RETRYCANCEL);
				switch (msBox)
				{
				case IDCANCEL:
					bird.free();
					delete[] obstacle;	// giải phóng bộ nhớ
					close();			// giải phóng dữ liệu
					return 0;

				case IDRETRY:
					goto retry;
				}
				//return 0;

			}

			bool win = isWin(bird.getRect());
			if (win)
			{
				Mix_PlayChannel(-1, gWin, 0);
				Mix_PauseMusic();
				int msBox = MessageBox(NULL, "====YOU WON====", "	====END GAME====", MB_RETRYCANCEL);
				switch (msBox)
				{
				case IDCANCEL:
					bird.free();
					delete[] obstacle;	// giải phóng bộ nhớ
					close();			// giải phóng dữ liệu
					return 0;

				case IDRETRY:
					goto retry;
				}
			}
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