#include "Cam.hpp"
#include "constants.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "utils.hpp"
#include <cstdlib>

#define IOR 1.25

Cam::Cam(const Point3 &_position, const Point3 &_target, const Vec3 &_upVector, 
         double _focalDistance, int _screenHeight, int _screenWidth)
        : position(_position), target(_target), upVector(_upVector), focalDistance(_focalDistance), 
            screenHeight(_screenHeight), screenWidth(_screenWidth) {
    calculateBasis();
    aspectRatio = double(screenWidth) / screenHeight;
}

void Cam::calculateBasis() {
    camForward = (position - target).normalized();
    camRight = upVector.cross(camForward).normalized();
    camUp = camForward.cross(camRight);
}

double randomOffset() {
    return (double)rand() / RAND_MAX;
}

Ray Cam::getPrimaryRay(int i, int j) const {
    double x_ = (j - 0.5 * screenWidth + randomOffset()) / screenWidth;
    double y_ = (i - 0.5 * screenHeight + randomOffset()) / screenHeight;
    
    double x = 2.0 * x_  * aspectRatio;
    double y = -2.0 * y_;

    // Calculates the direction of the primary ray
    Vec3 direction = -focalDistance * camForward 
                        + x * camRight
                        + y * camUp;

    // Creates primary ray with origin at camera position
    return Ray(position, direction.normalized());
}

Color Cam::shade(HitRecord& hitRecord, Scene& scene, Vec3& viewpointVec) const {
    Color color = hitRecord.material.getKa() * hitRecord.material.getOd() * scene.getAmbientColor();

    for (Light* light : scene.lightSources()) {
        viewpointVec = (position - hitRecord.point).normalized();
        Vec3 lightDirection = (light->getPosition() - hitRecord.point);
        double dist = lightDirection.length();
        lightDirection.inormalize();

        Ray shadowRay(hitRecord.point + 1e-2 * lightDirection, lightDirection);
        HitRecord shadowRec;
        scene.intersect(shadowRay, shadowRec);
        if (!shadowRec.hit || (shadowRec.distance > dist))
            color = color + light->illuminate(hitRecord, viewpointVec);
    }
    color.clamp();

    return color;
}

Color Cam::trace(const Ray& ray, Scene& scene, int depth) const {
    if (depth < 0)
        return BACKGROUND_COLOR;
    HitRecord hitRecord;
    
    scene.intersect(ray, hitRecord);
    if (!hitRecord.hit) {
        return BACKGROUND_COLOR;
    }

    Vec3 viewpointVec;
    Color color = shade(hitRecord, scene, viewpointVec);
    color.clamp();

    Vec3 reflected = reflectAroundNormal(viewpointVec, hitRecord.normal);
    Ray reflectedRay(hitRecord.point, reflected);
    Color kr = hitRecord.material.getKr();
    color = color + kr * trace(reflectedRay, scene, depth - 1);
    color.clamp();

    Color kt = hitRecord.material.getKt();
    if (kt.r != 0) {
        bool entering = ray.getDirection().dot(hitRecord.normal) < 0;
        double ratio = entering ? (1 / IOR) : IOR;

        double cos_theta = fmin((ray.getDirection()).dot(hitRecord.normal), 1);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
        if (ratio * sin_theta <= 1) {
            Vec3 r_out_perp = ratio * (ray.getDirection() + cos_theta * hitRecord.normal);
            Vec3 r_out_par = -sqrt(fabs(1 - r_out_perp.lengthSqr())) * hitRecord.normal;
            Vec3 refractionDir = r_out_par + r_out_perp;
            refractionDir.inormalize();
            
            
            Color rcolor = trace(Ray(hitRecord.point, refractionDir), scene, 1);
            rcolor.clamp();
            color = color + kt * rcolor;
        }
    } 

    return color;
}

Image Cam::render(Scene& scene, int aa_samples) {
    Image img(screenHeight, screenWidth);
    
    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            Color color(0, 0, 0);
            for (int sample = 0; sample < aa_samples; sample++) {
                Ray ray = getPrimaryRay(i, j);
                color = color + trace(ray, scene, 5);
            }
            color = color / aa_samples;
            color.clamp();
            img.setPixel(i, j, color);
        }
    }

    return img;
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

// --- For testing only ---

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