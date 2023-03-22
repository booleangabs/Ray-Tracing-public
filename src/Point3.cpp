#include "../include/Point3.hpp"

Point3::Point3() : x(0), y(0), z(0) {}

Point3::Point3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

double Point3::getX() const {
    return x;
}

double Point3::getY() const {
    return y;
}

double Point3::getZ() const {
    return z;
}

Point3 Point3::operator*(double scalar) const {
    return Point3(x * scalar, y * scalar, z * scalar);
}

Point3 operator*(double scalar, Point3 p) {
    return p * scalar;
}

Point3 Point3::operator/(double scalar) const {
    return Point3(x / scalar, y / scalar, z / scalar);
}
