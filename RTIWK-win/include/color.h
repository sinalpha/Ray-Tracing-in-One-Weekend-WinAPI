#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Windows.h>

#include "vec3.h"

using color = vec3;

void write_color(HDC, int, int, color);

#endif