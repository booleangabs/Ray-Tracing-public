#ifndef VEC3_H
#define VEC3_H

#include "Point3.hpp"
#include "math.h"

class Vec3 {
public:
    Vec3();
    Vec3(double x, double y, double z);
    Vec3(const Point3& from, const Point3& to);

    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void set(double x, double y, double z);

    double length() const;
    double lengthSqr() const;
    void inormalize();
    Vec3 normalized() const;
    
    Point3 operator+(const Point3& point) const;
    Vec3 operator+(const Vec3& vec) const;
    Vec3 operator*(const Vec3& vec) const;
    Vec3 operator*(double scalar) const;
    Vec3 operator-(const Vec3& vec) const;
    Vec3 operator-() const;
    bool operator==(const Vec3& vec) const;
    double dot(const Vec3& vec) const;
    Vec3 cross(const Vec3& vec) const;

private:
    double m_x, m_y, m_z;
};

Point3 operator+(const Point3& p, const Vec3& vec);
Vec3 operator*(double scalar, const Vec3& vec);
std::ostream& operator<<(std::ostream &s, const Vec3 &p);

#endif