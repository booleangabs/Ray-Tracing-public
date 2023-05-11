#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.hpp"
#include "Material.hpp"
#include "HitRecord.hpp"

class Object {
    public:
        virtual bool intersect(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const = 0;
};

#endif