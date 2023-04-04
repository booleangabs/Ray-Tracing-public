#include "Ray.hpp"

Ray::Ray() : origin(Point3()), direction(Vec3()) {};

Ray::Ray(const Point3& from, const Point3& to) {
    origin = from;
    direction = Vec3(from, to);
};

Ray::Ray(const Point3& _origin, const Vec3& _direction) {
    origin = _origin;
    direction = _direction;
};

Point3 Ray::getOrigin() const {
    return origin;
}

Vec3 Ray::getDirection() const {
    return direction;
}

void Ray::setOrigin(Point3 _origin) {
    origin = _origin;
}

void Ray::setDirection(Vec3 _direction) {
    direction = _direction;
}

void Ray::set(Point3 _origin, Vec3 _direction) {
    origin = _origin;
    direction = _direction;
}

Point3 Ray::at(double t) const {
    return origin + direction * t;
};
