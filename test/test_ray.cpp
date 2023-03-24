#include "Vec3.hpp"
#include "Point3.hpp"
#include "Ray.hpp"
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

string check_empty_init();
string check_two_points_init();
string check_point_vector_init();
string check_at();

int main(int argc, char ** argv) {
    bool ok;
    string status;
    string details;
    vector<string> prints;
    
    prints.push_back(check_empty_init());
    prints.push_back(check_two_points_init());
    prints.push_back(check_point_vector_init());
    prints.push_back(check_at());

    for (auto s : prints)
        cout << s << endl;
}

string check_empty_init() {
    string info = "Empty point should initialize both privaters vars to 0";
    Ray r;
    Point3 o = r.getOrigin();
    Vec3 v = r.getDirection();

    bool ok1 = o.getX() == 0 && o.getY() == 0 && o.getZ() == 0;
    bool ok2 = v.getX() == 0 && v.getY() == 0 && v.getZ() == 0;

    string status = get_check_status(ok1 && ok2);
    status += info;
    return status;
}

string check_two_points_init() {
    string info = "Initialize from two points";
    Point3 from(1.0, 1.0, 2.0), to(-1.0, 2.0, 2.5);
    Ray r(from, to);
    Vec3 v = r.getDirection();
    Point3 o = r.getOrigin();

    bool ok1 = o.getX() == 1.0 && o.getY() == 1.0 && o.getZ() == 2.0;
    bool ok2 = v.getX() == -2.0 && v.getY() == 1.0 && v.getZ() == 0.5;

    string status = get_check_status(ok1 && ok2);
    status += info;
    return status;
}

string check_point_vector_init() {
    string info = "Initialize from point and vector";
    Point3 origin = Point3();
    Vec3 dir(-1.0, 2.0, 2.5);

    Ray r(origin, dir);
    Point3 o = r.getOrigin();

    bool ok1 = o.getX() == 0.0 && o.getY() == 0.0 && o.getZ() == 0.0;
    bool ok2 = r.getDirection() == dir;

    string status = get_check_status(ok1 && ok2);
    status += info;
    return status;
}

string check_at() { 
    string info = "Vector addition";
    Vec3 u(1.0, 1.0, 2.0), v(-1.0, 2.0, 2.5);
    Vec3 w;
    w = u + v;
    w = v + u;

    bool ok = (w.getX() == 0.0) && (w.getY() == 3.0) && (w.getZ() == 4.5);

    string status = get_check_status(ok);
    status += info;
    return status;
};