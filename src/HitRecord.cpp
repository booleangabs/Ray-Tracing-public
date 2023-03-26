#include "../include/HitRecord.hpp"
#include "../include/Point3.hpp"
#include "../include/Vec3.hpp"
#include "../include/Material.hpp"

HitRecord::HitRecord(): t(0.0), point(0,0,0), normal(0,0,0), material((0,0,0)) {};
HitRecord::HitRecord(double t, const Point3& p,
 const Vec3& n, const Material& m): t(t), point(p), normal(n), material(m) {};
 