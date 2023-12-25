#ifndef INTERVAL_H
#define INTERVAL_H


#include "rtweekend.h"

class interval {
public:
    double min, max;

    interval();

    interval(double, double);

    bool contains(double) const;

    bool surrounds(double x) const;

    //무슨 문법인지 알아보기
    static const interval empty, universe;
};

//무슨 문법인지 알아보기
const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif