#include "../include/Cam.hpp"
#include "../include/Ray.hpp"
#include "Vec3.cpp"
#include "Point3.cpp"

Cam::Cam(const Point3& c, const Point3& m, const Vec3& vup,
           double d, double fovy,int vres, int hres) : C(c), M(m), Vup(vup), d(d), fovy(fovy), vres(vres), hres(hres) {
            setUVW();
            pixelSize = 2.0 * d * tan(fovy/2) / vres;
}

void Cam::setUVW(){
    //Defines the vectors u, v and w orthonormal
    w = -(Vec3(M.getX() - C.getX(), M.getY() - C.getY(), M.getZ() - C.getZ())).normalized();
    u = Vup.cross(w).normalized();
    v = w.cross(u).normalized();
}

Ray Cam::getPrimaryRay(int i, int j) const{
    // Calculates the coordinates of the center of the pixel on the screen
    double x = (i + 0.5) * pixelSize;
    double y = (j + 0.5) * pixelSize;

    // Calculates the direction of the primary ray
    Vec3 direction = -d*w + x*u + y*v;

    // Creates primary ray with origin at camera position
    return Ray(C, direction.normalized());
    
}