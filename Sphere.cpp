#include "Sphere.h"

Vec3 Sphere::getNormal(const Vec3& point) const {
    return normalize(point - origin);
}

double Sphere::intersect(const Ray& ray) const {
    Vec3 rayToSphere = ray.origin - origin;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(rayToSphere, ray.direction);
    double c = dot(rayToSphere, rayToSphere) - radius*radius;

    double discriminant = b*b - 4*a*c;
    if (discriminant > 0.0) {
        double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b - std::sqrt(discriminant)) / (2.0 * a);

        return (t1 < t2) ? t1 : t2;
    }

    return -1.0;
}