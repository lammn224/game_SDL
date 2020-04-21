#ifndef NHANVAT_H_
#define NHANVAT_H_

#include "HamChung.h" 

// kích thước nhân vật
#define width_NhanVat 89
#define heigth_NhanVat 89

class NhanVat : public HamChung		// Thừa kế lớp HamChung
{
public:
	NhanVat();
	~NhanVat();

	void NhapPhimDiChuyen(SDL_Event events);
	void Dichuyen();

private:
	// Giá trị thêm bớt vào tọa độ khi di chuyển ~~ tốc độ di chuyển
	int x_value;
	int y_value;
};

#endif