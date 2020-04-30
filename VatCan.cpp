#include "VatCan.h"
#include <ctime>

VatCan::VatCan()
{
	vitri.x = 0;
	vitri.y = 0;

	vitri.w = widthVatcan;
	vitri.h = heigthVatcan;

	// Giá trị thêm bớt vào tọa độ khi di chuyển ~~ tốc độ di chuyển
	x_value = 0;
}

VatCan::~VatCan()
{
}

void VatCan::DichuyenM()
{
	vitri.x -= x_value;

	// khi đi hết màn hình thì khởi tạo lại tại cuối màn hình
	if (vitri.x < 0)
	{
		//
		vitri.x = width;
		// khởi tạo giá trị ngẫu nhiên vị trí trên màn hình cho mỗi vật cản
		int random_y = rand() % 400;

		// nếu random lớn hơn chiều cao thì mặc định giá trị này
		if (random_y > heigth - 100) random_y = heigth * 3 / 10;

		vitri.y = random_y;
	}
}