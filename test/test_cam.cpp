#include "../include/Point3.hpp"
#include "../include/Vec3.hpp"
#include "../include/Ray.hpp"
#include "../include/Cam.hpp"
#include "../src/Ray.cpp"
#include "../src/Cam.cpp"
#include <iostream>
#include <vector>

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
    bool ok = (cam.w == Vec3(0,0,1) && cam.u == Vec3(1,0,0) && cam.v == Vec3(0,1,0));

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

    bool ok = (((generatedRay.getOrigin().getX() == expectedRay.getOrigin().getX()) && 
            (generatedRay.getOrigin().getY() == expectedRay.getOrigin().getY()) &&
            (generatedRay.getOrigin().getZ() == expectedRay.getOrigin().getZ())) &&
            (generatedRay.getDirection() == expectedRay.getDirection()));

    string status = get_check_status(ok);
    status += info;
    return status;
}
