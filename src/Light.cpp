#include "Light.hpp"
#include "math.h"

Light::Light() : mPosition(Point3()), mColor(Color(1, 1, 1)) {}

Light::Light(const Point3 &position, const Color &color) {
    mPosition = position;
    mColor = color;
}

Vec3 Light::getDirection(Point3 point) const{
    return (mPosition - point);
}

Color Light::illuminate(HitRecord& hitRecord, Vec3 direction, double atten) const {
    double NL = hitRecord.normal.dot(direction.normalized());
    Color diffuse =  hitRecord.material.getKd() * hitRecord.material.getOd() * NL;
    diffuse.clamp();

    Color specular;
    return  atten * mColor * (diffuse + specular);
}
