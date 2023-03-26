#ifndef HITRECORD_H
#define HITRECORD_H

#include "Point3.hpp"
#include "Vec3.hpp"
#include "Material.hpp"

class HitRecord {
public:
    HitRecord();
    HitRecord(double t, const Point3& p, const Vec3& n, const Material& m);
    double t;
    Point3 point;
    Vec3 normal;
    Material material;
};


#endif