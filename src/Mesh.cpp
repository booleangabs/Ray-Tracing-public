#include "Mesh.hpp"
#include "Vec3.hpp"
#include "constants.hpp"
#include "Triangle.hpp"
#include <limits>


Mesh::Mesh(const std::vector<Point3>& vertices, const std::vector<size_t>& indices, const Material& material)
    : m_vertices(vertices), m_indices(indices), m_material(material) {
        double n_vertices = m_vertices.size();
        double scale = 1 / n_vertices;
        m_normals = std::vector<Vec3>(n_vertices, Vec3());
        for (size_t i = 0; i < m_indices.size(); i += 3) {
            const Point3& v0 = m_vertices[m_indices[i]];
            const Point3& v1 = m_vertices[m_indices[i + 1]];
            const Point3& v2 = m_vertices[m_indices[i + 2]];
            Vec3 e1 = v1 - v0;
            Vec3 e2 = v2 - v0;
            Vec3 N = e1.cross(e2).normalized();
            m_normals[m_indices[i]] = m_normals[m_indices[i]] + N * scale;
            m_normals[m_indices[i + 1]] = m_normals[m_indices[i] + 1] + N * scale;
            m_normals[m_indices[i + 2]] = m_normals[m_indices[i] + 2] + N * scale;
        }
    }

bool Mesh::intersect(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const {
    bool hitAnything = false;
    double closestSoFar = t_max;

    for (size_t i = 0; i < m_indices.size(); i += 3) {
    const Point3& v0 = m_vertices[m_indices[i]];
    const Point3& v1 = m_vertices[m_indices[i + 1]];
    const Point3& v2 = m_vertices[m_indices[i + 2]];

    const Vec3& n0 = m_normals[m_indices[i]];
    const Vec3& n1 = m_normals[m_indices[i + 1]];
    const Vec3& n2 = m_normals[m_indices[i + 2]];

    Triangle triangle(v0, v1, v2, n0, n1, n2, m_material);
    if (triangle.intersect(ray, t_min, closestSoFar, hitRecord)) {
        hitAnything = true;
        closestSoFar = hitRecord.distance;
    }
    }

    return hitAnything;
}