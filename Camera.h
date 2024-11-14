#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"

struct Camera {
    Vec3 getDirection() const;
    Vec3 lookAt(const double u, const double v, const double aspectRatio);
    
    Vec3 position;
    Vec3 targetPosition;
    Vec3 up = { 0.0, 1.0, 0.0 };
    int sampleSize = 4;
};

#endif