#include "Cam.hpp"
#include "HitRecord.hpp"
#include "Object.hpp"
#include <limits>
#include <vector>
#include <memory>


Cam::Cam(const Point3 &_position, const Point3 &_target, const Vec3 &_upVector, 
         double _focalDistance, int _screenHeight, int _screenWidth)
        : position(_position), target(_target), upVector(_upVector), focalDistance(_focalDistance), 
            screenHeight(_screenHeight), screenWidth(_screenWidth) {
    calculateBasis();
    aspectRatio = double(screenWidth) / screenHeight;
    viewportWidth = 2.0 * aspectRatio;
    viewportHeight = 2.0;
}

void Cam::calculateBasis() {
    camForward = Vec3(target, position).normalized();
    camRight = upVector.cross(camForward).normalized();
    camUp = camForward.cross(camRight);
}

Ray Cam::getPrimaryRay(int i, int j) const {
    double x_ = (j + 0.5) / screenWidth;
    double y_ = (i + 0.5) / screenHeight;
    
    double x = (2.0 * x_ - 1.0) * aspectRatio;
    double y = (1.0 - 2.0 * y_);

    // Calculates the direction of the primary ray
    Vec3 direction = -focalDistance * camForward 
                        + x * camRight
                        + y * camUp;

    // Creates primary ray with origin at camera position
    return Ray(position, direction.normalized());
}

void Cam::setPosition(Point3 _position) {
    position = _position;
}

void Cam::setTarget(Point3 _target) {
    target = _target;
}

void Cam::setFocalDistance(double _focalDistance) {
    focalDistance = _focalDistance;
}

void Cam::setScreenHeight(double _screenHeight) {
    screenHeight = _screenHeight;
}

void Cam::setScreenWidth(double _screenWidth) {
    screenWidth = _screenWidth;
}

Point3 Cam::getPosition() {
    return position;
}

Point3 Cam::getTarget() {
    return target;
}

Vec3 Cam::getRightVector() {
    return camRight;
}

Vec3 Cam::getUpVector() {
    return camUp;
}

Vec3 Cam::getForwardVector() {
    return camForward;
}

double Cam::getFocalDistance() {
    return focalDistance;
}

double Cam::getScreenHeight() {
    return screenHeight;
}

double Cam::getScreenWidth() {
    return screenWidth;
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
}

Image Cam::dummyRenderXY() {
    Image img(screenHeight, screenWidth);
    
    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            img.setPixel(i, j, Color((float)i / screenHeight, (float)j / screenWidth, 0.0));
        }
    }

    return img;
}

Image Cam::dummyRenderRays() {
    Image img(screenHeight, screenWidth);
    
    double minx = std::numeric_limits<double>::max();
    double miny = std::numeric_limits<double>::max();
    double maxx = std::numeric_limits<double>::min();
    double maxy = std::numeric_limits<double>::min();

    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            Ray ray_ = getPrimaryRay(i, j);
            double rdx = ray_.getDirection().getX();
            double rdy = ray_.getDirection().getY();
            img.setPixel(i, j, Color(rdx, rdy, 0.0));

            if (rdx < minx) minx = rdx;
            else if (rdx > maxx) maxx = rdx;

            if (rdy < miny) miny = rdy;
            else if (rdy > maxy) maxy = rdy;
        }
    }


    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            Color curr = img.getPixel(i, j);
            double r = (curr.r - minx) / (maxx - minx);
            double g = (curr.g - miny) / (maxy - miny);
            img.setPixel(i, j, Color(r, g, 0.0));
        }
    }

    return img;
}