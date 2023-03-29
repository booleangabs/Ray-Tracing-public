#ifndef CAM_H
#define CAM_H

#include "Vec3.hpp"
#include "Point3.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Image.hpp"

class Cam {
    private:
        Point3 C; // Cam position
        Point3 M; // Where the cam it's pointing 
        Vec3 Vup; // Vector that points up
        Vec3 u, v, w; // Vectors
        double d; // Distance between the cam and screen
        double fovy; // Cam opening angle in y
        int vres; // Screen height
        int hres; // Screen width
        double pixelSize; // Pixel size
        
    public:
        Cam(const Point3& c, const Point3& m, const Vec3& vup,
            double d, double fovy, int vres, int hres);

        void calculateUVW();
        Ray getPrimaryRay(int i, int j) const;
        
        void setPosition(Point3 _C);
        void setTarget(Point3 _M);
        void setFocalDist(double _d);
        void setFov(double _fovy);
        void setVerticalRes(double _vres);
        void setHorizRes(double _hres);
        void setPixelSize(double _pixelSize);

        Point3 getC();
        Point3 getM();
        Vec3 getU();
        Vec3 getV();
        Vec3 getW();
        Point3 getPosition();
        Point3 getTarget();
        double getFocalDist();
        double getFov();
        double getVerticalRes();
        double getHorizRes();
        double getPixelSize();

        Color trace(const Ray& ray, int depth) const;

        Image dummy_render_xy();
        Image dummy_render_rays();
};

#endif