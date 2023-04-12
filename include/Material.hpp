#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.hpp"
#include "Color.hpp"

class Material {
    private:
        Color Od; // the base color
        Color kd, ks, ka, kr, kt;
        double n;

    public:
        Material(Color _Od, Color kd = Color(1, 1, 1), Color ks = Color(0.2, 0.2, 0.2), 
                 Color ka = Color(1, 1, 1), Color kr = Color(1, 1, 1), Color kt = Color(1, 1, 1),
                 double n = 1.0);

        Color getOd();
        Color getKd();
        Color getKs();
        Color getKa();
        Color getKr();
        Color getKt();
        double getN();
};

#endif