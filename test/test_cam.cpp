#include "Point3.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Cam.hpp"
#include "Ray.hpp"
#include "Cam.hpp"
#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

ostream& operator<<(ostream &s, const Vec3 &v) {
    return s << "Vec3(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
}

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

int main(int argc, char ** argv) {
    std::cout << "\n---Test Camera---" << std::endl;

    bool ok;
    string status;
    string details;
    vector<string> prints;

    prints.push_back(check_camera());
    prints.push_back(check_primary_ray());
    
    for (auto s : prints)
        cout << s << endl;
}

string check_camera() {
    string info = "Create the camera and setUVM correctly";
    Point3 c(0, 0, 0);
    Point3 m(0, 0, -1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 1.0;
    double fovy = 60.0;
    int screenWidth = 800;
    int screenHeight = 600;

    Cam cam(c, m, upVector, distanceToScreen, fovy, screenHeight, screenWidth);
    bool ok = (cam.getW() == Vec3(0,0,1) && cam.getU() == Vec3(1,0,0) && cam.getV() == Vec3(0,1,0));

    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_primary_ray() {
    string info = "Create the primary ray correctly";
    Point3 c(0, 0, 0);
    Point3 m(0, 0, -1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 1.0;
    double fovy = 60.0;
    int screenWidth = 800;
    int screenHeight = 600;

    Cam cam(c, m, upVector, distanceToScreen, fovy, screenHeight, screenWidth);

    Point3 expectedOrigin = c;
    Vec3 expectedDirection = Vec3(-0.213703, -0.213703, -0.953238);
    Ray expectedRay(expectedOrigin, expectedDirection);

    Ray generatedRay = cam.getPrimaryRay(10, 10);
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
