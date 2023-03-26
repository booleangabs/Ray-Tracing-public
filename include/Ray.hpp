#ifndef RAY_H
#define RAY_H

#include "Vec3.hpp"
#include "Point3.hpp"

class Ray {    
    private:
        Point3 orig;
        Vec3 dir;
    public:
        Ray(const Point3& origin, const Vec3& direction);

        Point3 origin() const { return orig; }
        Vec3 direction() const { return dir; }

        Point3 at(double t) const {
            return orig + t*dir;
        }

        bool operator==(const Ray& ray) const;
};

#endif