#ifndef COLOR_H
#define COLOR_H

class Color {
    public:
        double r, g, b;

        Color(double r = 0, double g = 0, double b = 0);

        Color operator*(const Color& c) const;
        Color operator*(double s) const;
        Color operator/(double s) const;
        Color operator+(const Color& c) const;
        Color operator-(const Color& c) const;

        void clamp();
};

Color operator*(double scalar, Color p);

#endif