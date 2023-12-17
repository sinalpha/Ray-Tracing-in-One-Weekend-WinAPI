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


// point3�� vec3�� �����ϻ� ���ٸ� ����� ����.
// �׷��� �ڵ带 © �� �������� ����Կ��� ������ �ȴ�.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream&, const vec3&);
inline vec3 operator+(const vec3&, const vec3&);
inline vec3 operator-(const vec3&, const vec3&);
inline vec3 operator*(const vec3& , const vec3&);
inline vec3 operator*(double, const vec3&);
inline vec3 operator*(const vec3&, double);
inline vec3 operator/(vec3 , double);
inline double dot(const vec3&, const vec3&);
inline vec3 cross(const vec3&, const vec3&);
inline vec3 unit_vector(vec3);

#endif