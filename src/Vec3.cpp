#include "../include/Vec3.hpp"
// #include "Vec3.hpp"

Vec3::Vec3() : x(0), y(0), z(0) {};

Vec3::Vec3(double _x, double _y, double _z)
    : x(_x), y(_y), z(_z) {};

Vec3::Vec3(const Point3& from, const Point3& to) {
    x = to.getX() - from.getX();
    y = to.getY() - from.getY();
    z = to.getZ() - from.getZ();
};

double Vec3::getX() const {
    return x;
}

double Vec3::getY() const {
    return y;
}

double Vec3::getZ() const {
    return z;
}

// Length
double Vec3::length() const {
    return sqrt(x * x + y * y + z * z);
};

// Length squared
double Vec3::lengthSqr() const {
    return x * x + y * y + z * z;
};

// In-place normalization
void Vec3::inormalize() {
    double l = length();
    x /= l;
    y /= l;
    z /= l;
};

// Normalization
Vec3 Vec3::normalized() const {
    double l = length();
    return Vec3(x / l, y / l, z / l);
};

// Vector addition
Vec3 Vec3::operator+(const Vec3& vec) const {
    return Vec3(x + vec.getX(), y + vec.getY(), z + vec.getZ());
};

// Vector-point addition
Point3 Vec3::operator+(const Point3& point) const {
    return Point3(x + point.getX(), y + point.getY(), z + point.getZ());
};

Point3 operator+(const Point3& point, const Vec3& vec) {
    return vec + point;
}

// Vector subtraction
Vec3 Vec3::operator-(const Vec3& vec) const {
    return Vec3(x - vec.getX(), y - vec.getY(), z - vec.getZ());
};

// Vector negative
Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
};

// Element-wise vector multiplication
Vec3 Vec3::operator*(const Vec3& vec) const {
    return Vec3(x * vec.getX(), y * vec.getY(), z * vec.getZ());
};

// Scalar multiplication
Vec3 Vec3::operator*(double scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 operator*(double scalar, const Vec3& vec) {
    return vec * scalar;
}

bool Vec3::operator==(const Vec3 &vec) const
{
    return (x == vec.getX()) & (y == vec.getY()) & (z == vec.getZ());
};

// Dot product
double Vec3::dot(const Vec3& vec) const {
    return x * vec.getX() + y * vec.getY() + z * vec.getZ();
};

// Cross product
Vec3 Vec3::cross(const Vec3& vec) const {
    double a = (y * vec.getZ() - vec.getY() * z);
    double b = (z * vec.getX() - vec.getZ() * x);
    double c = (x * vec.getY() - vec.getX() * y);
    return Vec3(a, b, c);
};