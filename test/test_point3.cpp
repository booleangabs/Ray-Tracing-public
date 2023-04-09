#include "Point3.hpp"
#include "Vec3.hpp"
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

string check_empty_init();
string check_multiply();
string check_division();
string check_subtraction();

int main(int argc, char ** argv) {
    std::cout << "\n---Test Point3---" << std::endl;

    bool ok;
    string status;
    string details;
    vector<string> prints;
    
    prints.push_back(check_empty_init());
    prints.push_back(check_multiply());
    prints.push_back(check_division());
    prints.push_back(check_subtraction());

    for (auto s : prints)
        cout << s << endl;
}

string check_empty_init() {
    string info = "Empty point should initialize to origin";
    Point3 p;
    bool ok = (p == Point3(0, 0, 0));
    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_multiply() {
    string info = "Scalar multiplication (double sided)";
    Point3 p(1.0, 1.0, 1.0);

    Point3 q = p * 2.0;
    bool ok1 = (q == Point3(2.0, 2.0, 2.0));

    q = 3.0 * p;
    bool ok2 = (q == Point3(3.0, 3.0, 3.0));

    string status = get_check_status(ok1 && ok2);
    status += info;
    return status;
}

string check_division() {
    string info = "Scalar division";
    Point3 p(1.0, 1.0, 1.0);
    Point3 q = p / 2.0;
    bool ok = (q == Point3(0.5, 0.5, 0.5));
    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_subtraction() {
    string info = "Vector from point subtraction";
    Point3 p(1.0, 1.0, 1.0);
    Point3 q = p / 2.0;

    Vec3 v = p - q;
    bool ok = (v == Vec3(0.5, 0.5, 0.5));
    string status = get_check_status(ok);
    status += info;
    return status;
}