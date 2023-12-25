#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

// Common Headers

#include "ray.h"
#include "vec3.h"


// Usingss

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double);


#endif