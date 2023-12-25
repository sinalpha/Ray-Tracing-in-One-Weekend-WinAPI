#include "../include/interval.h"

interval::interval() 
    : min(+infinity), max(-infinity) {}

interval::interval(double _min, double _max) 
    : min(_min), max(_max) {}

bool interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}