#include "HitRecord.hpp"

HitRecord::HitRecord() : distance(0.0), point(0,0,0), normal(0,0,0), material((0,0,0)) {};

HitRecord::HitRecord(double _distance, const Point3& _point, const Vec3& _normal, const Material& _material)
                : distance(_distance), point(_point), normal(_normal), material(_material) {};
 