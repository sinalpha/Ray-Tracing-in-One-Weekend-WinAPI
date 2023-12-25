#include "../include/sphere.h"

sphere::sphere(point3 center_, double radius_) : center(center_), radius(radius_) {}

bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {

	vec3 oc{ r.origin() - center };
	double a{ r.direction().length_squared() };
	double half_b{ dot(oc, r.direction()) };
	double c{ oc.length_squared() - radius * radius };

	double discriminant{ half_b * half_b - a * c };
	if (discriminant < 0)
		return false;
	double sqrtd{ sqrt(discriminant) };

	//허용 범위 내에 가장 가까운 root 값 찾기
	double root{ (-half_b - sqrtd) / a };
	if (root <= ray_tmin || ray_tmax <= root) {
		root = (-half_b + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	// 그냥 빼는 것은 안과 밖을 정할 수 없으므로 set_face_normal에서 dot 곱을 해야함.
	vec3 outward_normal{ rec.p - center / radius };
	rec.set_face_normal(r, outward_normal);

	return true;
}