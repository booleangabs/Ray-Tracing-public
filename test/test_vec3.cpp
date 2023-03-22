#include "Vec3.hpp"
#include "Point3.hpp"
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
string check_point_init();
string check_length();
string check_vec_addition();
string check_vec_point_add();
string check_elementwise_prod();
string check_scalar_multiply();
string check_vec_subtraction();
string check_vec_negative();
string check_dot_product();
string check_cross_product();


int main(int argc, char ** argv) {
    bool ok;
    string status;
    string details;
    vector<string> prints;
    
    prints.push_back(check_empty_init());
    prints.push_back(check_point_init());
    prints.push_back(check_length());
    prints.push_back(check_vec_addition());
    prints.push_back(check_vec_point_add());
    prints.push_back(check_elementwise_prod());
    prints.push_back(check_scalar_multiply());
    prints.push_back(check_vec_subtraction());
    prints.push_back(check_vec_negative());
    prints.push_back(check_dot_product());
    prints.push_back(check_cross_product());

    for (auto s : prints)
        cout << s << endl;
}

string check_empty_init() {
    string info = "Empty point should initialize to origin";
    Vec3 v;
    bool ok = (v.getX() == 0.0) && (v.getY() == 0.0) && (v.getZ() == 0.0);
    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_point_init() {
    string info = "Initialize from points";
    Point3 from(1.0, 1.0, 2.0), to(-1.0, 2.0, 2.5);
    Vec3 v(from, to);

    bool ok = (v.getX() == -2.0) && (v.getY() == 1.0) && (v.getZ() == 0.5);

    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_length() {
    string info = "Length";
    Vec3 v(2.0, 0.0, 2.0);

    bool ok = v.length() == (2.0 * sqrt(2));

    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_vec_addition() { 
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

string check_vec_point_add() {
    string info = "Vector-point add (double sided)";
    Vec3 v(1.0, 1.0, 2.0);
    Point3 p(-1.0, 2.0, 2.5);
    Point3 q;

    q = p + v;
    q = v + p;

    bool ok = (q.getX() == 0.0) && (q.getY() == 3.0) && (q.getZ() == 4.5);

    string status = get_check_status(ok);
    status += info;
    return status;
};

string check_elementwise_prod() {
    string info = "Vector elementwise multiplication";
    Vec3 u(1.0, 1.0, 2.0), v(-1.0, 2.0, 2.5);
    Vec3 w;
    w = u * v;
    w = v * u;

    bool ok = (w.getX() == -1.0) && (w.getY() == 2.0) && (w.getZ() == 5.0);

    string status = get_check_status(ok);
    status += info;
    return status;
};

string check_scalar_multiply() { 
    string info = "Scalar multiplication (double sided)";
    Vec3 v(1.0, 1.0, 1.0);

    Vec3 u = v * 2.0;
    bool ok1 = (u.getX() == 2.0) && (u.getY() == 2.0) && (u.getZ() == 2.0);

    u = 3.0 * v;
    bool ok2 = (u.getX() == 3.0) && (u.getY() == 3.0) && (u.getZ() == 3.0);

    string status = get_check_status(ok1 & ok2);
    status += info;
    return status;
};

string check_vec_subtraction() {
    string info = "Vector subtraction";
    Vec3 u(1.0, 1.0, 2.0), v(-1.0, 2.0, 2.5);
    Vec3 w;
    w = u - v;
    w = v - u;

    bool ok = (w.getX() == -2.0) && (w.getY() == 1.0) && (w.getZ() == 0.5);

    string status = get_check_status(ok);
    status += info;
    return status;
};

string check_vec_negative() { 
    string info = "Negative";
    Vec3 v(-1.0, 2.0, 2.5);
    v = -v;

    bool ok = (v.getX() == 1.0) && (v.getY() == -2.0) && (v.getZ() == -2.5);

    string status = get_check_status(ok);
    status += info;
    return status;
};

string check_dot_product() { 
    string info = "Dot product";
    Vec3 u(1.0, 0.0, 0.0), v(0.0, 1.0, 0.0);
    
    double a = v.dot(u);
    double b = u.dot(v);

    bool ok = (a == b) & (a == 0.0);

    string status = get_check_status(ok);
    status += info;
    return status;
};

string check_cross_product() {
    string info = "Cross product";
    Vec3 u(1.0, 0.0, 0.0), v(0.0, 1.0, 0.0);

    Vec3 w = u.cross(v);
    Vec3 z = v.cross(u);

    bool ok = (w == -z) & (w.getZ() == 1.0);

    string status = get_check_status(ok);
    status += info;
    return status;
};