#include <Windows.h>

#include "../include/color.h"

void write_color(HDC hdc, int x, int y, color pixel_color){
    //RGB의 각 값을 [0,255]으로 바꾼 값을 쓴다. 
    SetPixel(hdc, x, y, RGB(
        static_cast<int>(255.999 * pixel_color.x()),
        static_cast<int>(255.999 * pixel_color.y()),
        static_cast<int>(255.999 * pixel_color.z())
    ));

}