#include "Sphere.hpp"
#include "Ray.hpp"
#include "constants.hpp"
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

string check_init();
string check_intersection();
string check_no_intersection();

int main(int argc, char ** argv) {
    std::cout << "\n---Test Sphere---" << std::endl;

    bool ok;
    string status;
    string details;
    vector<string> prints;
    
    prints.push_back(check_init());
    prints.push_back(check_intersection());
    prints.push_back(check_no_intersection());

    for (auto s : prints)
        cout << s << endl;
}

string check_init() {
    string info = "Initialization";
    Sphere sp(Point3(0, 5, 5), 2.5, Material(Color(0.25, 0, 0.25)));
    bool ok = true; // if got past the last line (may add actual checks if getters are added)
    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_intersection() {
    string info = "Ray intersection";
    Sphere sp(Point3(0, 0, 0), 1.0, Material(Color(0.33, 0, 0.25)));
    Ray ray(Point3(0, 0, 5), Vec3(0, 0, -1));

    HitRecord r;
    bool ok1 = sp.intersect(ray, EPSILON, T_MAX, r);
    bool ok2 = (r.distance == 4.0);
    bool ok3 = (r.point == Point3(0, 0, 1));
    bool ok4 = (r.normal == Vec3(0, 0, 1));
    Color c = r.material.getOd();
    bool ok5 = (c.r == 0.33) && (c.g == 0.0) && (c.b == 0.25);
    string status = get_check_status(ok1 && ok2 && ok3 && ok4 && ok5);
    status += info;
    return status;
}

string check_no_intersection() {
    string info = "Ray without intersection";
    Sphere sp(Point3(0, 0, 0), 1.0, Material(Color(0.66, 1, 0.75)));
    Ray ray(Point3(5, 5, 0), Vec3(0, 0, 1));

    HitRecord r;
    bool ok = !sp.intersect(ray, EPSILON, T_MAX, r);
    string status = get_check_status(ok);
    status += info;
    return status;
}