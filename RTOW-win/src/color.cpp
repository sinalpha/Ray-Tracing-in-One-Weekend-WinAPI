#include <Windows.h>

#include "../include/color.h"

void write_color(HDC hdc, int x, int y, color pixel_color){
    //RGB�� �� ���� [0,255]���� �ٲ� ���� ����. 
    SetPixel(hdc, x, y, RGB(
        static_cast<int>(255.999 * pixel_color.x()),
        static_cast<int>(255.999 * pixel_color.y()),
        static_cast<int>(255.999 * pixel_color.z())
    ));

}