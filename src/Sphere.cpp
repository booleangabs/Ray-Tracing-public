#include "Sphere.hpp"
#include "math.h"

Sphere::Sphere(const Point3& center, const double& radius, const Material& material)
            : m_center(center), m_radius(radius), m_material(material) {}

bool Sphere::intersect(const Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const {
    Vec3 oc = ray.getOrigin() - m_center;
    double ocr = oc.dot(ray.getDirection());
    double ocsr2 = oc.lengthSqr() - m_radius * m_radius;

    auto discriminant = ocr * ocr - ocsr2;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double t = (-ocr - sqrtd);
    if (t < t_min) {
        t = (-ocr + sqrtd);
        if (t < t_min)
            return false;
    }

    hitRecord.distance = t;
    hitRecord.point = ray.at(t);
    hitRecord.normal = (hitRecord.point - m_center).normalized();
    hitRecord.material = m_material;

    return true;
}
