#include "Point3.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Cam.hpp"
#include "Ray.hpp"
#include "Cam.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

string get_check_status(bool ok) {
    string status;
    switch (ok) {
        case 1:
            status = "PASSED: ";
            break;
        default:
            status = "FAILED: ";
            break;
    };
    return status;
}

string check_camera();
string check_primary_ray();
void do_render(int cam_mode, std::string path);

int main(int argc, char ** argv) {
    std::cout << "\n---Test Camera---" << std::endl;

    if (argc < 3) {
        std::cout << "Usage: ./test_cam.(o/exe) <output/file/path> cam_mode" << std::endl;
        return -1;
    }
    const std::string path = (std::string) argv[1];
    const int cam_mode = atoi(argv[2]);

    bool ok;
    string status;
    string details;
    vector<string> prints;

    prints.push_back(check_camera());
    // prints.push_back(check_primary_ray());
     
    for (auto s : prints)
        cout << s << endl;

    do_render(cam_mode, path);
}

string check_camera() {
    string info = "Create the camera and setUVM correctly";
    Point3 c(0, 0, 0);
    Point3 m(0, 0, -1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 1.0;
    int screenWidth = 800;
    int screenHeight = 600;

    Cam cam(c, m, upVector, distanceToScreen, screenHeight, screenWidth);
    bool ok = (cam.getForwardVector() == Vec3(0,0,1) 
                && cam.getRightVector() == Vec3(1,0,0) 
                && cam.getUpVector() == Vec3(0,1,0));

    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_primary_ray() {
    // TODO: check ray generation and fix this test
    string info = "Create the primary ray correctly";
    Point3 c(0, 0, 0);
    Point3 m(0, 0, -1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 1.0;
    int screenWidth = 640;
    int screenHeight = 480;

    Cam cam(c, m, upVector, distanceToScreen, screenHeight, screenWidth);

    Point3 expectedOrigin = c;
    Vec3 expectedDirection = Vec3(-0.213703, -0.213703, -0.953238);
    Ray expectedRay(expectedOrigin, expectedDirection);

    Ray generatedRay = cam.getPrimaryRay(0, 0);
    Point3 generatedOrigin = generatedRay.getOrigin();
    
    Vec3 diff = (generatedRay.getDirection() - expectedRay.getDirection());
    bool ok1 = (std::abs(diff.getX()) < 1e-5) && (std::abs(diff.getY()) < 1e-5) && (std::abs(diff.getZ()) < 1e-5);
    bool ok2 = (generatedOrigin.getX() == expectedOrigin.getX()) &&
                (generatedOrigin.getY() == expectedOrigin.getY()) &&
                (generatedOrigin.getZ() == expectedOrigin.getZ());

    string status = get_check_status(ok1 && ok2);
    status += info;
    return status;
}

void do_render(int cam_mode, std::string path) {
    Point3 c(7.5, 7.5, 7.5);
    Point3 m(1, 1, 1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 5;
    double scale = 1;
    int screenWidth = int(640 * scale);
    int screenHeight = int(480 * scale);

    Cam cam(c, m, upVector, distanceToScreen, screenHeight, screenWidth);

    Image result(screenHeight, screenWidth);

    switch (cam_mode) {
        case 0:
            result = cam.dummyRenderXY();
            break;
        
        case 1:
            result = cam.dummyRenderRays();
            break;

        default:
            Scene scene(Color(0.25, 0.25, 0.25));
            
            Material wall1(Color(0.95, 0.5, 0.5));
            Material wall2(Color(0.5, 0.95, 0.5));
            Material wall3(Color(0.5, 0.5, 0.95));
            Material highlighted_ball(Color(1, 1, 1));
            highlighted_ball.setKs(Color(1, 1, 1) * 0.75);
            highlighted_ball.setEta(50);

            Plane p1(Point3(), upVector, wall1);
            Plane p2(Point3(), Vec3(1, 0, 0), wall2);
            Plane p3(Point3(), Vec3(0, 0, 1), wall3);
            Sphere sp1(Point3(), 1.0, Material(Color(0.75, 0.75, 0.75)));
            Sphere sp2(Point3(0.45, 1.3, 0.45), 0.25, highlighted_ball);
            Sphere sp3(Point3(1.3, 0.45, 0.45), 0.25, highlighted_ball);
            Sphere sp4(Point3(0.45, 0.45, 1.3), 0.25, highlighted_ball);

            Light l1(Point3(2, 1, 1), Color(1, 0, 0));
            Light l2(Point3(1, 1, 2), Color(0, 1, 0));
            Light l3(Point3(1, 2, 1), Color(0, 0, 1));

            scene.addObject(&sp1);
            scene.addObject(&sp2);
            scene.addObject(&sp3);
            scene.addObject(&sp4);
            scene.addObject(&p1);
            scene.addObject(&p2);
            scene.addObject(&p3);

            scene.addLight(&l1);
            scene.addLight(&l2);
            scene.addLight(&l3);
            
            result = cam.render(scene);
            break;
    }

    result.save(path);
}