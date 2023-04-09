#ifndef SPHERE_H
#define SPHERE_H

#include "Point3.hpp"
#include "Object.hpp"

class Sphere : public Object {
public:
    Sphere(const Point3& center, const double& radius, const Material& material);

    bool intersect(const Ray& ray, double t_min, HitRecord& hitRecord) const override;

private:
    Point3 m_center;
    double m_radius;
    Material m_material;
};

#endif
