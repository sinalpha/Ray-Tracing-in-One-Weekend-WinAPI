#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	ray();

	ray(const point3&, const vec3& );

	point3 origin() const;
	vec3 direction() const;

	point3 at(double) const;

private:
	point3 orig;
	vec3 dir;
};

#endif