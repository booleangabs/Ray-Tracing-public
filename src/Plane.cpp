#include "Plane.hpp"
#include "constants.hpp"

Plane::Plane(const Point3& point, const Vec3& normal, const Material& material)
    : m_point(point), m_normal(normal.normalized()), m_material(material) {};

bool Plane::intersect(const Ray& ray, double t_min, HitRecord& hitRecord) const {
    double denom = ray.getDirection().dot(m_normal);
    if (std::abs(denom) < EPSILON) {
        return false;
    }

    double t = (m_point - ray.getOrigin()).dot(m_normal) / denom;
    if (t < 0) {
        return false;
    }

    hitRecord.distance = t;
    hitRecord.point = ray.at(t);
    hitRecord.normal = m_normal;
    hitRecord.material = m_material;

    return true;
}