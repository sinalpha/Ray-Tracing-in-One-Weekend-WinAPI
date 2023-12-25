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

    //���� �������� �˾ƺ���
    static const interval empty, universe;
};

//���� �������� �˾ƺ���
const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif