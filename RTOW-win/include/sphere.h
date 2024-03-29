#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"
#include "interval.h"
#include "hittable.h"

class sphere : public hittable {
public:

	sphere(point3, double, shared_ptr<material>);
	bool hit(const ray&, interval, hit_record&) const override;

private:
	point3 center;
	double radius;
	shared_ptr<material> mat;
};

#endif