#include "Material.hpp"

Material::Material(Color _Od, Color _kd, Color _ks, 
                 Color _ka, Color _kr, Color _kt,
                 double _eta) 
        : Od(_Od), kd(_kd), ks(_ks), ka(_ka), kr(_kr), kt(_kt), eta(_eta) {};

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

double Material::getEta() {
    return eta;
}

void Material::setOd(Color _Od) {
    Od = _Od;
}

void Material::setKd(Color _Kd) {
    kd = _Kd;
}

void Material::setKs(Color _Ks) {
    ks = _Ks;
}

void Material::setKa(Color _Ka) {
    ks = _Ka;
}

void Material::setKr(Color _Kr) {
    kr = _Kr;
}

void Material::setKt(Color _Kt) {
    kt = _Kt;
}

void Material::setEta(double _Eta) {
    eta = _Eta;
}
