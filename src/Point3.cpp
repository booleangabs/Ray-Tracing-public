#include "Point3.hpp"

class Point3
{
private:
    double x, y, z;
public:
    Point3() : x(0.0), y(0.0), z(0.0) {}
    Point3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

     Point3 operator/(double scalar) const {
        return Point3(x/scalar, y/scalar, z/scalar);
    }

     Point3 operator*(double scalar) const {
        return Point3(x*scalar, y*scalar, z*scalar);
    }
};
