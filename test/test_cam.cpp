#include "../include/Point3.hpp"
#include "../include/Vec3.hpp"
#include "../include/Ray.hpp"
#include "../include/Cam.hpp"
#include "../src/Ray.cpp"
#include "../src/Cam.cpp"
#include <iostream>
#include <vector>

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
string check_ray();

int main(int argc, char ** argv) {
    bool ok;
    string status;
    string details;
    vector<string> prints;

    prints.push_back(check_camera());
    prints.push_back(check_ray());
    
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

string check_ray() {
    string info = "Create the camera and the ray is correctly created";
    Point3 c(0, 0, 0);
    Point3 m(0, 0, -1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 1.0;
    double fovy = 60.0;
    int screenWidth = 800;
    int screenHeight = 600;

    Cam cam(c, m, upVector, distanceToScreen, fovy, screenHeight, screenWidth);
    Point3 expectedOrigin = c;
    Vec3 expectedDirection = Vec3(-0.224187, -0.224187, -1).normalized();
    Ray expectedRay(expectedOrigin, expectedDirection);

    Ray generatedRay = cam.getPrimaryRay(10, 10);
    
    bool ok = (generatedRay == expectedRay);
    string status = get_check_status(ok);
    status += info;
    return status;
}
