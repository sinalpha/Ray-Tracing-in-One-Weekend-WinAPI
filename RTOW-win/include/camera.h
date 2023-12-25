#ifndef CAMERA_H
#define CAMERA_H

#include <Windows.h>

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0;  
    int    image_width  = 100; 
    int    image_height;   

    /* Public Camera Parameters Here */
    void render(HDC, const hittable&);

private:
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    /* Private Camera Variables Here */
    void initialize();
    color ray_color(const ray& r, const hittable& world) const;
};

#endif