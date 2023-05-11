#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Object.hpp"
#include "Point3.hpp"
#include "Material.hpp"

class Mesh : public Object {
public:
    Mesh(const std::vector<Point3>& vertices, const std::vector<size_t>& indices, const Material& material);
    virtual bool intersect(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const override;

private:
    std::vector<Point3> m_vertices;
    std::vector<Vec3> m_normals;
    std::vector<size_t> m_indices;
    Material m_material;
};

#endif