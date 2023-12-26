#include <Windows.h>

#include "../include/color.h"
#include "../include/interval.h"

void write_color(HDC hdc, int x, int y, color pixel_color, int samples_per_pixel){
    double r{ pixel_color.x() };
    double g{ pixel_color.y() };
    double b{ pixel_color.z() };
    

    double scale{ 1.0 / samples_per_pixel };
    r *= scale;
    g *= scale;
    b *= scale;

    //RGB의 각 값을 [0,255]으로 바꾼 값을 쓴다. 
    static const interval intensity(0.000, 0.999);
    SetPixel(hdc, x, y, RGB(
        static_cast<int>(256 * intensity.clamp(r)),
        static_cast<int>(256 * intensity.clamp(g)),
        static_cast<int>(256 * intensity.clamp(b))
    ));

}
