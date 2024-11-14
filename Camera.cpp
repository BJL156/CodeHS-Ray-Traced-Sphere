#include "Camera.h"

Vec3 Camera::getDirection() const {
    return normalize(targetPosition - position);
}

Vec3 Camera::lookAt(const double u, const double v, const double aspectRatio) {
    Vec3 direction = getDirection();
    return normalize(direction + up * v + cross(direction, up) * u * aspectRatio);
}