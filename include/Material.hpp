#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.hpp"
#include "Color.hpp"

class Material {
    private:
        Color Od; // the base color
        Color kd, ks, ka, kr, kt;
        double eta;

    public:
        Material(Color _Od, Color _kd = Color(1, 1, 1), Color _ks = Color(), 
                 Color _ka = Color(1, 1, 1), Color _kr = Color(1, 1, 1), Color _kt = Color(1, 1, 1),
                 double _eta = 1.0);

        Color getOd();
        Color getKd();
        Color getKs();
        Color getKa();
        Color getKr();
        Color getKt();
        double getEta();

        void setOd(Color _Od);
        void setKd(Color _Kd);
        void setKs(Color _Ks);
        void setKa(Color _Ka);
        void setKr(Color _Kr);
        void setKt(Color _Kt);
        void setEta(double _Eta);
};

#endif