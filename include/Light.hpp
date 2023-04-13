#ifndef LIGHT_H
#define LIGHT_H

#include "Point3.hpp"
#include "Color.hpp"
#include "HitRecord.hpp"

class Light {
    private:
        Point3 mPosition;
        Color mIntensity;

        Vec3 reflectAroundNormal(Vec3 direction, Vec3 normal) const;

    public:
        Light();
        Light(const Point3& position, const Color& color = Color(1, 1, 1));

        Vec3 getDirection(Point3 point) const;
        Point3 getPosition() const;

        Color getIntensity() const;
        Color illuminate(HitRecord hitRecord, Vec3 viewpointVec, bool inShadow);
};

#endif