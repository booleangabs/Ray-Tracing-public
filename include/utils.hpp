#ifndef UTILS_H
#define UTILS_H

#include "Vec3.hpp"

Vec3 reflectAroundNormal(Vec3 direction, Vec3 normal) {
    return 2 * normal.dot(direction) * normal - direction;
}

#endif