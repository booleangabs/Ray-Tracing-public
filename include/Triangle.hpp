#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "Object.hpp"
#include "Point3.hpp"
#include "Material.hpp"

class Triangle : public Object {
public:
    Triangle(const Point3& v0, const Point3& v1, const Point3& v2,
             const Vec3& n0, const Vec3& n1, const Vec3& n2,
             const Material& material);
    virtual bool intersect(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const override;

private:
    Point3 m_v0;
    Point3 m_v1;
    Point3 m_v2;
    Vec3 m_n0;
    Vec3 m_n1;
    Vec3 m_n2;
    Material m_material;
};

#endif