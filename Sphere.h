#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Material.h"
#include "Ray.h"

struct Sphere {
    Vec3 getNormal(const Vec3& point) const;
    double intersect(const Ray& ray) const;
    
    Vec3 origin;
    double radius;
    Material material;
};

#endif