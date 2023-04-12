#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.hpp"
#include "Color.hpp"

class Material {
    private:
        Color albedo; // the "main" color
        Color kd, ks, ka, kr, kt;
        double n;

    public:
        Material(Color _albedo, Color kd = Color(1, 1, 1), Color ks = Color(1, 1, 1), 
                 Color ka = Color(1, 1, 1), Color kr = Color(1, 1, 1), Color kt = Color(1, 1, 1),
                 double n = 1.0);

        Color getAlbedo();
        Color getKd();
        Color getKs();
        Color getKa();
        Color getKr();
        Color getKt();
        double getN();
};

#endif