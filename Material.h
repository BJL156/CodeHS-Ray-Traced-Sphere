#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec3.h"

struct Material {
    Vec3 albedo;
    bool diffuse;
};

#endif