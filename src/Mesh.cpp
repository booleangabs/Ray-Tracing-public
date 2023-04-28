#include "Mesh.hpp"
#include "Vec3.hpp"
#include "constants.hpp"
#include <limits>


Mesh::Mesh(const std::vector<Point3>& vertices, const std::vector<size_t>& indices, const Material& material)
    : m_vertices(vertices), m_indices(indices), m_material(material) {}

bool Mesh::intersect(const Ray& ray, double t_min, HitRecord& hitRecord) const {
    bool hitAnything = false;
    double closest_t = std::numeric_limits<double>::max();
    HitRecord closestHitRecord;
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        const Point3& v0 = m_vertices[m_indices[i]];
        const Point3& v1 = m_vertices[m_indices[i+1]];
        const Point3& v2 = m_vertices[m_indices[i+2]];
        const Vec3 edge1 = v1 - v0;
        const Vec3 edge2 = v2 - v0;
        const Vec3 normal = edge1.cross(edge2).normalized();

        const double denom = normal.dot(ray.getDirection());
        if (std::abs(denom) > EPSILON) {
            const double t = normal.dot(v0 - ray.getOrigin()) / denom;
            if (t > t_min && t < closest_t) {
                const Point3 p = ray.at(t);

                const Vec3 w = p - v0;
                /*
                    The Barycentric coordinates u, v are defined as the ratios of the areas of the sub-triangles
                    formed by the intersection point and the vertices of the triangle to the area of the entire triangle. 
                */
                const double u = edge2.cross(w).dot(normal) / edge1.cross(edge2).dot(normal);
                const double v = edge1.cross(w).dot(normal) / edge1.cross(edge2).dot(normal);
                if (u >= 0 && v >= 0 && u + v <= 1) {
                    hitAnything = true;
                    closest_t = t;
                    closestHitRecord.distance = t;
                    closestHitRecord.point = p;
                    closestHitRecord.normal = normal;
                    closestHitRecord.material = m_material;
                }
            }
        }
    }
    if (hitAnything) {
        hitRecord = closestHitRecord;
    }
    return hitAnything;
}