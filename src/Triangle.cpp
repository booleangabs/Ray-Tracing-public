#include "Triangle.hpp"
#include "constants.hpp"

Triangle::Triangle(const Point3& v0, const Point3& v1, const Point3& v2, 
                    const Vec3& n0, const Vec3& n1, const Vec3& n2,
                    const Material& material)
    : m_v0(v0), m_v1(v1), m_v2(v2), m_n0(n0), m_n1(n1), m_n2(n2), m_material(material) {}

bool Triangle::intersect(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const {
    // Calculate the edges of the triangle
    Vec3 e1 = m_v1 - m_v0;
    Vec3 e2 = m_v2 - m_v0;

    // Calculate the normal of the triangle
    Vec3 p = ray.getDirection().cross(e2);
    double det = e1.dot(p);

    // Check if the ray is parallel to the triangle
    if (det > -EPSILON && det < EPSILON) {
        return false;
    }

    // Calculate u parameter of the barycentric coordinate and test bounds 
    double invDet = 1.0 / det;
    Vec3 t = ray.getOrigin() - m_v0;
    double u = t.dot(p) * invDet;

    if (u < 0.0 || u > 1.0) {
        return false;
    }

    // Calculate v parameter of the barycentric coordinate and test bounds 
    Vec3 q = t.cross(e1);
    double v = ray.getDirection().dot(q) * invDet;

    // Check if the ray intersects the triangle
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    // Calculate t, intersection point and normal
    double tHit = e2.dot(q) * invDet;
    if (tHit < t_min || tHit > t_max) {
        return false;
    }

    hitRecord.distance = tHit;
    hitRecord.point = ray.at(hitRecord.distance);
    hitRecord.normal = u * m_n0 + v * m_n1 + (1 - u - v) * m_n2;
    hitRecord.material = m_material;

    return true;
}