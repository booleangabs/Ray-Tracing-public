#ifndef RAY_H
#define RAY_H

#include "Point3.hpp"
#include "Vec3.hpp"

class Ray {
    private:
        Point3 origin;
        Vec3 direction;

    public:
        Ray();
        Ray(const Point3& point1, const Point3& point2);
        Ray(const Point3& _origin, const Vec3& _direction);

        Point3 at(double t) const;
};

#endif