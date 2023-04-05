#include "Point3.hpp"

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

void Point3::setX(double _x) {
    x = _x;
}

void Point3::setY(double _y) {
    y = _y;
}

void Point3::setZ(double _z) {
    z = _z;
}

void Point3::set(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
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

bool Point3::operator==(Point3 other) const {
    return (x == other.getX())
            && (y == other.getY())
            && (z == other.getZ());
}