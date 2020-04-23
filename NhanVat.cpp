#include "NhanVat.h"
NhanVat::NhanVat()
{
	vitri.x = 0;
	vitri.y = 0;

	vitri.w = width_NhanVat;
	vitri.h = heigth_NhanVat;

	// Giá trị thêm bớt vào tọa độ khi di chuyển ~~ tốc độ di chuyển
	x_value = 0;
	y_value = 0;
}

NhanVat::~NhanVat()
{
}

void NhanVat::NhapPhimDiChuyen(SDL_Event events)
{
	// nhấn phím -> gán tốc độ di chuyển
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_value = y_value - heigth_NhanVat / 35;
			break;
		case SDLK_DOWN:
			y_value = y_value + heigth_NhanVat / 35;
			break;
		case SDLK_RIGHT:
			x_value = x_value + heigth_NhanVat / 25;
			break;
		case SDLK_LEFT:
			x_value = x_value - heigth_NhanVat / 25;
			break;
		default:
			break;
		}
	}
	// nhấc phím gán lại tốc độ về 0
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_value = 0;
			break;
		case SDLK_DOWN:
			y_value = 0;
			break;
		case SDLK_RIGHT:
			x_value = 0;
			break;
		case SDLK_LEFT:
			x_value = 0;
			break;
		default:
			break;
		}
	}
}

void NhanVat::Dichuyen()
{
	vitri.x += x_value;
	//cout << "vitri.x = " << vitri.x << "			x_value = " << x_value << endl;
	// nếu quá màn hình -> không di chuyển
	if (vitri.x < 0 || vitri.x + width_NhanVat > width + 50) vitri.x -= x_value;
	//x_value = 0;

	vitri.y += y_value;
	// nếu quá màn hình -> không di chuyển
	if (vitri.y < 0 || vitri.y + heigth_NhanVat > heigth - 100) vitri.y -= y_value;
	//y_value = 0;
}

