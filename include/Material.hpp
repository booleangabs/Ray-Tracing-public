#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

class Material {
public:
    Material(const Color& c);
    Color shade(const Ray& ray, const HitRecord& hit);
private:
    Color color;
};

#endif