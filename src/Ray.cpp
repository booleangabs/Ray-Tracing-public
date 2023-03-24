#include "../include/Ray.hpp"

Ray::Ray() : origin(Point3()), direction(Vec3()) {};

Ray::Ray(const Point3& point1, const Point3& point2) {
    origin = point1;
    direction = Vec3(point1, point2);
};

Ray::Ray(const Point3& _origin, const Vec3& _direction) {
    origin = _origin;
    direction = _direction;
};

Point3 Ray::at(double t) const {
    return origin + direction * t;
};