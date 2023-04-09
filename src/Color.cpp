#include "../include/Color.hpp"

Color::Color(double r, double g, double b): r(r), g(g), b(b) {};

Color Color::operator*(const Color& c) const {
    return Color(r * c.r, g * c.g, b * c.b);
};

Color Color::operator*(double s) const {
    return Color(r * s, g * s, b * s);
};

Color Color::operator/(double s) const {
    return Color(r / s, g / s, b / s);
};

Color Color::operator+(const Color& c) const {
    return Color(r + c.r, g + c.g, b + c.b);
};

Color Color::operator-(const Color& c) const {
    return Color(r - c.r, g - c.g, b - c.b);
}

void Color::clamp() {
    r = r > 1 ? 1 : r < 0 ? 0 : r;
    g = g > 1 ? 1 : g < 0 ? 0 : g;
    b = b > 1 ? 1 : b < 0 ? 0 : b;
}

Color operator*(double s, Color c) {
    return c * s;
};