#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3.h"

struct Light {
    Vec3 origin;
    Vec3 intensity;
};

#endif