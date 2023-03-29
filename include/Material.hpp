#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

class Material {
    private:
        Color albedo; // the "main" color
        Vec3 kd, ks, ka, kr, kt;
        double n;

    public:
        Material(Color _albedo, Vec3 kd = Vec3(), Vec3 ks = Vec3(), 
                 Vec3 ka = Vec3(), Vec3 kr = Vec3(), Vec3 kt = Vec3(),
                 double n = 1.0);

        Color getAlbedo();
        Vec3 getKd();
        Vec3 getKs();
        Vec3 getKa();
        Vec3 getKr();
        Vec3 getKt();
        double getN();
};

#endif