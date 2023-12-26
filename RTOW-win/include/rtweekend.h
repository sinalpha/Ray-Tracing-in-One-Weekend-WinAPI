#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <random>
#include <memory>

#include "ray.h"
#include "vec3.h"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

constexpr double infinity{ std::numeric_limits<double>::infinity() };
constexpr double pi{ 3.1415926535897932385 };

// Utility Functions
double degrees_to_radians(double);
double random_double();
double random_double(double, double);





#endif