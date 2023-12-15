#include "../include/color.h"

void write_color(std::ostream& out, color pixel_color){
    //RGB의 각 값을 [0,255]으로 바꾼 값을 쓴다. 
     out << static_cast<int>(255.999 * pixel_color.x()) << ' '
         << static_cast<int>(255.999 * pixel_color.y()) << ' '
         << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}