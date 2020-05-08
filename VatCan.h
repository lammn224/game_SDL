#ifndef VatCan_H_
#define VatCan_H_

#include "HamChung.h"

// kích thước vật cản
#define widthVatcan 89
#define heigthVatcan 89

class VatCan : public HamChung		// Thừa kế lớp action chung
{
public:
	VatCan();
	~VatCan();

	void DichuyenM();
	// gán tốc độ di chuyển cho vật cản
	void setX_value(int value) {
		x_value = value;
	}

private:
	// Giá trị thêm bớt vào tọa độ khi di chuyển ~~ tốc độ di chuyển
	int x_value;
};

#endif