#include "Vec3.hpp"

Vec3::Vec3() : m_x(0), m_y(0), m_z(0) {};

Vec3::Vec3(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z) {};

Vec3::Vec3(const Point3& from, const Point3& to) {
    m_x = to.getX() - from.getX();
    m_y = to.getY() - from.getY();
    m_z = to.getZ() - from.getZ();
};

double Vec3::getX() const {
    return m_x;
}

double Vec3::getY() const {
    return m_y;
}

double Vec3::getZ() const {
    return m_z;
}

void Vec3::setX(double x) {
    m_x = x;
}

void Vec3::setY(double y) {
    m_y = y;
}

void Vec3::setZ(double z) {
    m_z = z;
}

void Vec3::set(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

// Length
double Vec3::length() const {
    return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
};

// Length squared
double Vec3::lengthSqr() const {
    return m_x * m_x + m_y * m_y + m_z * m_z;
};

// In-place normalization
void Vec3::inormalize() {
    double l = length();
    m_x /= l;
    m_y /= l;
    m_z /= l;
};

// Normalization
Vec3 Vec3::normalized() const {
    double l = length();
    return Vec3(m_x / l, m_y / l, m_z / l);
};

// Vector addition
Vec3 Vec3::operator+(const Vec3& vec) const {
    return Vec3(m_x + vec.getX(), m_y + vec.getY(), m_z + vec.getZ());
};

// Vector-point addition
Point3 Vec3::operator+(const Point3& point) const {
    return Point3(m_x + point.getX(), m_y + point.getY(), m_z + point.getZ());
};

Point3 operator+(const Point3& point, const Vec3& vec) {
    return vec + point;
}

// Vector subtraction
Vec3 Vec3::operator-(const Vec3& vec) const {
    return Vec3(m_x - vec.getX(), m_y - vec.getY(), m_z - vec.getZ());
};

// Vector negative
Vec3 Vec3::operator-() const {
    return Vec3(-m_x, -m_y, -m_z);
};

// Element-wise vector multiplication
Vec3 Vec3::operator*(const Vec3& vec) const {
    return Vec3(m_x * vec.getX(), m_y * vec.getY(), m_z * vec.getZ());
};

// Scalar multiplication
Vec3 Vec3::operator*(double scalar) const {
    return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
}

Vec3 operator*(double scalar, const Vec3& vec) {
    return vec * scalar;
}

bool Vec3::operator==(const Vec3 &vec) const
{
    return (m_x == vec.getX()) & (m_y == vec.getY()) & (m_z == vec.getZ());
};

// Dot product
double Vec3::dot(const Vec3& vec) const {
    return m_x * vec.getX() + m_y * vec.getY() + m_z * vec.getZ();
};

// Cross product
Vec3 Vec3::cross(const Vec3& vec) const {
    double a = (m_y * vec.getZ() - vec.getY() * m_z);
    double b = (m_z * vec.getX() - vec.getZ() * m_x);
    double c = (m_x * vec.getY() - vec.getX() * m_y);
    return Vec3(a, b, c);
};