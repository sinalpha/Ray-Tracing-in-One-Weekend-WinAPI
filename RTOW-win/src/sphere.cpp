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

	//��� ���� ���� ���� ����� root �� ã��
	double root{ (-half_b - sqrtd) / a };
	if (root <= ray_tmin || ray_tmax <= root) {
		root = (-half_b + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	// �׳� ���� ���� �Ȱ� ���� ���� �� �����Ƿ� set_face_normal���� dot ���� �ؾ���.
	vec3 outward_normal{ rec.p - center / radius };
	rec.set_face_normal(r, outward_normal);

	return true;
}