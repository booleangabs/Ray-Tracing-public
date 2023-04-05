#ifndef POINT3_H
#define POINT3_H

#include <iostream>

class Point3 {
    private:
        double x, y, z;

    public:
        Point3();
        Point3(double _x, double _y, double _z);

        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double _x);
        void setY(double _y);
        void setZ(double _z);
        void set(double _x, double _y, double _z);

        Point3 operator/(double scalar) const;
        Point3 operator*(double scalar) const;
        bool operator==(Point3 other) const;
};

Point3 operator*(double scalar, Point3 p);

std::ostream& operator<<(std::ostream &s, const Point3 &p) {
    return s << "Point3(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
}

#endif