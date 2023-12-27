#ifndef COLOR_H
#define COLOR_H

#include <Windows.h>

#include "interval.h"
#include "vec3.h"
#include "color.h"

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}

inline void write_color(HDC hdc, int x, int y, color pixel_color, int samples_per_pixel) {
    double r{ pixel_color.x() };
    double g{ pixel_color.y() };
    double b{ pixel_color.z() };


    double scale{ 1.0 / samples_per_pixel };
    r *= scale;
    g *= scale;
    b *= scale;

    // 감마 2 보정  
    // linear -> gamma (->는 a루트을 곱하는 것)
    // gamma -> linear (->는 a제곱을 곱하는 것)
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    //RGB의 각 값을 [0,255]으로 바꾼 값을 쓴다. 
    static const interval intensity(0.000, 0.999);
    SetPixel(hdc, x, y, RGB(
        static_cast<int>(256 * intensity.clamp(r)),
        static_cast<int>(256 * intensity.clamp(g)),
        static_cast<int>(256 * intensity.clamp(b))
    ));

}
#endif