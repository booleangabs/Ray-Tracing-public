#ifndef POINT3_H
#define POINT3_H

class Point3 {
    private:
        double x, y, z;
    public:
        Point3();
        Point3(double _x, double _y, double _z);
        double getX() const;
        double getY() const;
        double getZ() const;
        Point3 operator/(double scalar) const;
        Point3 operator*(double scalar) const;
};

Point3 operator*(double scalar, Point3 p);

#endif