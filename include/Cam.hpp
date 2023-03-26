#ifndef CAM_H
#define CAM_H

#include "Vec3.hpp"
#include "Point3.hpp"
#include "Ray.hpp"

class Cam {
public:
    Cam(const Point3& c, const Point3& m, const Vec3& vup,
           double d, double fovy,int vres, int hres);
    void setUVW();

    Ray getPrimaryRay(int i, int j) const;

    Vec3 u, v, w; // Vectors
private:
    Point3 C; // Cam position
    Point3 M; // Where the cam it's pointing 
    Vec3 Vup; // Vector that points up
    double d; // Distance between the cam and screen
    double fovy; // Cam opening angle in y
    int vres; // Screen height
    int hres; // Screen width
    double pixelSize; // Pixel size
};

#endif