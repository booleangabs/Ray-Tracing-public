#ifndef HITRECORD_H
#define HITRECORD_H

#include "Point3.hpp"
#include "Vec3.hpp"
#include "Material.hpp"

class HitRecord {
    public:
        double distance;
        Point3 point;
        Vec3 normal;
        Material material;

        HitRecord();
        HitRecord(double _distance, const Point3& _point, const Vec3& _normal, const Material& _material);
};


#endif