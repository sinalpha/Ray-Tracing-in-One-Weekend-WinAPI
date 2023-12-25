#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:

	sphere(point3, double);
	bool hit(const ray&, double, double, hit_record&) const override;

private:
	point3 center;
	double radius;
};

#endif