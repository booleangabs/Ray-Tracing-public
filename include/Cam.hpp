#ifndef CAM_H
#define CAM_H

#include "Ray.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "HitRecord.hpp"
#include "Object.hpp"
#include <limits>
#include <vector>
#include <memory>

class Cam {
    private:
        Point3 position; // Cam position
        Point3 target; // Where the cam it's pointing 
        Vec3 upVector; // Vector that points up
        Vec3 camRight, camUp, camForward; // Vectors
        double focalDistance; // Distance between the cam and screen
        int screenWidth; 
        int screenHeight;
        double aspectRatio;
        double viewportWidth;
        double viewportHeight;
        
    public:
        Cam(const Point3& _position, const Point3& _target, const Vec3& _upVector,
            double _focalDistance, int _screenHeight, int _screenWidth);

        void calculateBasis();
        Ray getPrimaryRay(int i, int j) const;
        Color trace(const Ray& ray, Scene& scene, int depth) const;
        Image render(Scene& scene);
        
        void setPosition(Point3 _position);
        void setTarget(Point3 _target);
        void setFocalDistance(double _focalDistance);
        void setScreenHeight(double _screenHeight);
        void setScreenWidth(double _screenWidth);

        Point3 getPosition();
        Point3 getTarget();
        Vec3 getRightVector();
        Vec3 getUpVector();
        Vec3 getForwardVector();
        double getFocalDistance();
        double getScreenHeight();
        double getScreenWidth();

        Image dummyRenderXY();
        Image dummyRenderRays();
};

#endif