#include "Cam.hpp"
#include "HitRecord.hpp"
#include "Object.hpp"
#include <limits>
#include <vector>
#include <memory>

Cam::Cam(const Point3& c, const Point3& m, const Vec3& vup,
         double d, double fovy,int vres, int hres) 
        : C(c), M(m), Vup(vup), d(d), fovy(fovy), vres(vres), hres(hres) {
    calculateUVW();
    pixelSize = 2.0 * d * tan(fovy/2) / vres;
};

void Cam::calculateUVW(){
    //Defines the vectors u, v and w orthonormal
    w = Vec3(M, C).normalized();
    u = Vup.cross(w).normalized();
    v = w.cross(u);
};

Ray Cam::getPrimaryRay(int i, int j) const {
    // Calculates the coordinates of the center of the pixel on the screen
    double x = (j - (hres / 2) + 0.5) * pixelSize;
    double y = -(i - (vres / 2) + 0.5) * pixelSize;

    // Calculates the direction of the primary ray
    Vec3 direction = d*w - x*u - y*v;

    // Creates primary ray with origin at camera position
    return Ray(C, direction.normalized());
};

void Cam::setPosition(Point3 _C) {
    C = _C;
}

void Cam::setTarget(Point3 _M) {
    M = _M;
}

void Cam::setFocalDist(double _d) {
    d = _d;
}

void Cam::setFov(double _fovy) {
    fovy = _fovy;
}

void Cam::setVerticalRes(double _vres) {
    vres = _vres;
}

void Cam::setHorizRes(double _hres) {
    hres = _hres;
}

void Cam::setPixelSize(double _pixelSize) {
    pixelSize = _pixelSize;
}

Point3 Cam::getC() {
    return C;
}

Point3 Cam::getM() {
    return M;
}

Vec3 Cam::getU() {
    return u;
}

Vec3 Cam::getV() {
    return v;
}

Vec3 Cam::getW() {
    return w;
}

Point3 Cam::getPosition() {
    return C;    
}

Point3 Cam::getTarget() { 
    return M;
}

double Cam::getFocalDist() { 
    return d;
}

double Cam::getFov() { 
    return fovy;
}

double Cam::getVerticalRes() { 
    return vres;
}

double Cam::getHorizRes() { 
    return hres;
}

double Cam::getPixelSize() { 
    return pixelSize;
}

Color Cam::trace(const Ray& ray, int depth) const {
    HitRecord hitRecord;
    Color color;

    // Find closest intersection
    // double tMin = std::numeric_limits<double>::infinity();
    // for (const auto& obj : objects) {
    //     if (obj->intersect(ray, tMin, hitRecord)) {
    //         tMin = hitRecord.t;
    //         color = hitRecord.material.shade(ray, hitRecord);
    //     }
    // }

    return color;
};

Image Cam::dummy_render_xy() {
    Image img(vres, hres);
    
    for (int i = 0; i < vres; i++) {
        for (int j = 0; j < hres; j++) {
            img.setPixel(i, j, Color((float)i / vres, (float)j / hres, 0.0));
        }
    }

    return img;
}

Image Cam::dummy_render_rays() {
    Image img(vres, hres);
    
    double minx = std::numeric_limits<double>::max();
    double miny = std::numeric_limits<double>::max();
    double minz = std::numeric_limits<double>::max();
    double maxx = std::numeric_limits<double>::min();
    double maxy = std::numeric_limits<double>::min();
    double maxz = std::numeric_limits<double>::min();

    for (int i = 0; i < vres; i++) {
        for (int j = 0; j < hres; j++) {
            Ray ray_ = getPrimaryRay(i, j);
            double rdx = ray_.getDirection().getX();
            double rdy = ray_.getDirection().getY();
            double rdz = ray_.getDirection().getZ();
            img.setPixel(i, j, Color(rdx, rdy, rdz));

            if (rdx < minx) minx = rdx;
            else if (rdx > maxx) maxx = rdx;

            if (rdy < miny) miny = rdy;
            else if (rdy > maxy) maxy = rdy;

            if (rdz < minz) minz = rdz;
            else if (rdz > maxz) maxz = rdz;
        }
    }


    for (int i = 0; i < vres; i++) {
        for (int j = 0; j < hres; j++) {
            Color curr = img.getPixel(i, j);
            double r = (curr.r - minx) / (maxx - minx);
            double g = (curr.g - miny) / (maxy - miny);
            double b = (curr.b - minz) / (maxz - minz);
            img.setPixel(i, j, Color(r, g, b));
        }
    }

    return img;
}