#ifndef POINT3_H
#define POINT3_H

#include <iostream>

class Vec3;

class Point3 {
    private:
        double m_x, m_y, m_z;

    public:
        Point3();
        Point3(double x, double y, double z);

        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double x);
        void setY(double y);
        void setZ(double z);
        void set(double x, double y, double z);

        Point3 operator/(double scalar) const;
        Point3 operator*(double scalar) const;
        Vec3 operator-(Point3 other) const;
        bool operator==(Point3 other) const;
};

Point3 operator*(double scalar, Point3 p);

std::ostream& operator<<(std::ostream &s, const Point3 &p);

#endif