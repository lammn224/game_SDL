#ifndef HAMCHUNG_H_
#define HAMCHUNG_H_

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

class HamChung
{
public:
	HamChung();
	//	constructor : được định nghĩa bằng cách đặt tên Constructor 
	//	trùng với tên class và không có kiểu trả về.

	~HamChung();
	//	destructor : được định nghĩa bằng cách đặt tên Destructor 
	//	trùng với tên class và thêm ký tự ~ vào phía trước.

	bool LoadAnh(string path, SDL_Renderer* screen);		// hàm load ảnh qua đường dẫn

	void Render(SDL_Renderer* des);			// hàm update hình ảnh lên màn hình

	void free();

	void setRect(const int &x, const int &y)		// hàm cài đặt vị trí ban đầu vật thể
	{
		vitri.x = x;
		vitri.y = y;
	}

	SDL_Rect getRect()				// trả về vị trí vật thể
	{
		return vitri;
	}

protected:				// thừa kế
	SDL_Texture* object;
	SDL_Rect vitri;

};

#endif // !HAMCHUNG_H_

