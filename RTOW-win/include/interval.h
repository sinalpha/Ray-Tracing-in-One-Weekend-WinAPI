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
    //���ø��ϰ� ���� ��
    double clamp(double) const;


    //���� �������� �˾ƺ���
    static const interval empty, universe;
};


const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif
