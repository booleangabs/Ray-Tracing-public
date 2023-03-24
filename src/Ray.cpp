#include "../include/Ray.hpp"

Ray::Ray() : origin(Point3()), direction(Vec3()) {};

Ray::Ray(const Point3& from, const Point3& to) {
    origin = from;
    direction = Vec3(from, to);
};

Ray::Ray(const Point3& _origin, const Vec3& _direction) {
    origin = _origin;
    direction = _direction;
};

Point3 Ray::getOrigin() {
    return origin;
}

Vec3 Ray::getDirection() {
    return direction;
}

Point3 Ray::at(double t) const {
    return origin + direction * t;
};