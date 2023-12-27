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

    // ���� 2 ����  
    // linear -> gamma (->�� a��Ʈ�� ���ϴ� ��)
    // gamma -> linear (->�� a������ ���ϴ� ��)
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    //RGB�� �� ���� [0,255]���� �ٲ� ���� ����. 
    static const interval intensity(0.000, 0.999);
    SetPixel(hdc, x, y, RGB(
        static_cast<int>(256 * intensity.clamp(r)),
        static_cast<int>(256 * intensity.clamp(g)),
        static_cast<int>(256 * intensity.clamp(b))
    ));

}
#endif