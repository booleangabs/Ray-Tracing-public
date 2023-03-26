#include "../include/Material.hpp"

Material::Material(const Color& c): color(c) {};

Color Material::shade(const Ray& ray, const HitRecord& hit) {
    return color;
};