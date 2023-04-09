#include "Material.hpp"

Material::Material(Color _albedo, Vec3 _kd, Vec3 _ks, 
                 Vec3 _ka, Vec3 _kr, Vec3 _kt,
                 double _n) 
        : albedo(_albedo), kd(_kd), ks(_ks), ka(_ka), kr(_kr), kt(_kt), n(_n) {};

Color Material::getAlbedo() {
    return albedo;
}

Vec3 Material::getKd() {
    return kd;
}

Vec3 Material::getKs() {
    return ks;
}

Vec3 Material::getKa() {
    return ka;
}

Vec3 Material::getKr() {
    return kr;
}

Vec3 Material::getKt() {
    return kt;
}

double Material::getN() {
    return n;
}
