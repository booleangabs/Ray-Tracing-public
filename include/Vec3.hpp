#ifndef VEC3_H
#define VEC3_H

#include "Point3.hpp"
#include "math.h"

class Vec3{
    private:
        double x, y, z;

    public:
        Vec3();
        Vec3(double _x, double _y, double _z);
        Vec3(const Point3& from, const Point3& to);

        double getX() const;
        double getY() const;
        double getZ() const;

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

        double dot(const Vec3& vec) const;
        Vec3 cross(const Vec3& vec) const;

        bool operator==(const Vec3& vec) const;
};

Point3 operator+(const Point3& p, const Vec3& vec);
Vec3 operator*(double scalar, const Vec3& vec);

#endif