#include "Light.hpp"
#include "math.h"

Light::Light() : mPosition(Point3()), mIntensity(Color(1, 1, 1)) {}

Light::Light(const Point3 &position, const Color &color) {
    mPosition = position;
    mIntensity = color;
}

Color Light::illuminate(HitRecord hitRecord, Vec3 viewpointVec) {
    Point3 hitPoint = hitRecord.point;
    Vec3 normal = hitRecord.normal;
    Material mtrl = hitRecord.material;

    Vec3 direction = getDirection(hitPoint);
    double distanceAttenuation = 1 / direction.length();
    direction.inormalize();

    double ndotl = std::max(0.0, normal.dot(direction));
    Color diffuseTerm = mtrl.getKd() * mtrl.getOd() * ndotl;

    Vec3 reflection = reflectAroundNormal(direction, normal);
    double rdotv = std::max(0.0, viewpointVec.dot(reflection));
    Color specularTerm = mtrl.getKs() * std::pow(rdotv, mtrl.getEta());

    double f_att = distanceAttenuation;
    return f_att * mIntensity * (diffuseTerm + specularTerm);
}

Color Light::getIntensity() const {
    return mIntensity;
}

Vec3 Light::reflectAroundNormal(Vec3 direction, Vec3 normal) const {
    return 2 * normal.dot(direction) * normal - direction;
}

Vec3 Light::getDirection(Point3 point) const{
    return (mPosition - point);
}

Point3 Light::getPosition() const {
    return mPosition;
}
