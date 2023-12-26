#ifndef INTERVAL_H
#define INTERVAL_H

#include <random>
#include "rtweekend.h"

class interval {
public:
    double min, max;

    interval();
    interval(double, double);

    bool contains(double) const;
    bool surrounds(double) const;
    //샘플링하고 나서 씀
    double clamp(double) const;


    //무슨 문법인지 알아보기
    static const interval empty, universe;
};


const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif
