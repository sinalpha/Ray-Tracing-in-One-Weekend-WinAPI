#ifndef VEC3_H
#define VEC3_H


#include <iostream>

using std::sqrt;

class vec3 {
public:
	double e[3];

	vec3();
	vec3(double, double, double);

	double x() const;
	double y() const;
	double z() const;

	vec3 operator-() const;
	double operator[](int) const;
	double& operator[](int);

	vec3& operator+=(const vec3&);
	vec3& operator*=(double);
	vec3& operator/=(double);
	double length() const;
	double length_squared() const;
};


// point3는 vec3의 재명명일뿐 별다른 기능은 없다.
// 그러나 코드를 짤 때 기하학적 명료함에는 도움이 된다.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}



#endif