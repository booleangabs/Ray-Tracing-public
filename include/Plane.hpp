#ifndef PLANE_H
#define PLANE_H

#include "Object.hpp"
#include "Point3.hpp"
#include "Vec3.hpp"
#include "Material.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

class Plane : public Object {
public:
    Plane(const Point3& point, const Vec3& normal, const Material& material);
    bool intersect(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const override;
private:
    Point3 m_point;
    Vec3 m_normal;
    Material m_material;
};

#endif