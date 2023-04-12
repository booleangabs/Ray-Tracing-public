#include "Material.hpp"

Material::Material(Color _Od, Color _kd, Color _ks, 
                 Color _ka, Color _kr, Color _kt,
                 double _n) 
        : Od(_Od), kd(_kd), ks(_ks), ka(_ka), kr(_kr), kt(_kt), n(_n) {};

Color Material::getOd() {
    return Od;
}

Color Material::getKd() {
    return kd;
}

Color Material::getKs() {
    return ks;
}

Color Material::getKa() {
    return ka;
}

Color Material::getKr() {
    return kr;
}

Color Material::getKt() {
    return kt;
}

double Material::getN() {
    return n;
}
