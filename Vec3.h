#ifndef VEC3_H
#define VEC3_H

#include "Utils.h"

#include <cmath>

struct Vec3 {
    Vec3();
    Vec3(double x);
    Vec3(double x, double y, double z);
    ~Vec3() = default;
    
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

// Vector vs vector
Vec3 operator+(const Vec3& v0, const Vec3& v1);
Vec3 operator-(const Vec3& v0, const Vec3& v1);
Vec3 operator*(const Vec3& v0, const Vec3& v1);
Vec3 operator/(const Vec3& v0, const Vec3& v1);

// Scalar vs vector
Vec3 operator+(double t, const Vec3& v0);
Vec3 operator-(double t, const Vec3& v0);
Vec3 operator*(double t, const Vec3& v0);
Vec3 operator/(double t, const Vec3& v0);

// Vector vs scalar
Vec3 operator+(const Vec3& v0, double t);
Vec3 operator-(const Vec3& v0, double t);
Vec3 operator*(const Vec3& v0, double t);
Vec3 operator/(const Vec3& v0, double t);

Vec3 operator-(const Vec3& v0);

double dot(const Vec3& v0, const Vec3& v1);
double lengthSquared(const Vec3& v0);
double length(const Vec3& v0);
Vec3 normalize(const Vec3& v0);
Vec3 randomVec3();
Vec3 randomVec3(double min, double max);
Vec3 randomUnitVector();
Vec3 randomVec3Hemisphere(const Vec3& normal);
Vec3 cross(const Vec3& v0, const Vec3& v1);
Vec3 clamp(const Vec3& v, double min, double max);

#endif