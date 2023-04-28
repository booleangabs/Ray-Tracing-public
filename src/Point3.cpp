#include "Point3.hpp"
#include "Vec3.hpp"

Point3::Point3() : m_x(0), m_y(0), m_z(0) {}

Point3::Point3(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

double Point3::getX() const {
    return m_x;
}

double Point3::getY() const {
    return m_y;
}

double Point3::getZ() const {
    return m_z;
}

void Point3::setX(double x) {
    m_x = x;
}

void Point3::setY(double y) {
    m_y = y;
}

void Point3::setZ(double z) {
    m_z = z;
}

void Point3::set(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

Point3 Point3::operator*(double scalar) const {
    return Point3(m_x * scalar, m_y * scalar, m_z * scalar);
}

Vec3 Point3::operator-(Point3 other) const {
    return Vec3(m_x - other.getX(), m_y - other.getY(), m_z - other.getZ());
}

Point3 operator*(double scalar, Point3 p) {
    return p * scalar;
}

Point3 Point3::operator/(double scalar) const {
    return Point3(m_x / scalar, m_y / scalar, m_z / scalar);
}

bool Point3::operator==(Point3 other) const {
    return (m_x == other.getX())
            && (m_y == other.getY())
            && (m_z == other.getZ());
}

std::ostream& operator<<(std::ostream &s, const Point3 &p) {
    return s << "Point3(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
}