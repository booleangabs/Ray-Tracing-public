#include "Point3.hpp"
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream &s, const Point3 &p) {
    return s << "Point3(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
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
string check_multiply();
string check_division();

int main(int argc, char ** argv) {
    std::cout << "\n---Test Point3---" << std::endl;

    bool ok;
    string status;
    string details;
    vector<string> prints;
    
    prints.push_back(check_empty_init());
    prints.push_back(check_multiply());
    prints.push_back(check_division());

    for (auto s : prints)
        cout << s << endl;
}

string check_empty_init() {
    string info = "Empty point should initialize to origin";
    Point3 p;
    bool ok = (p.getX() == 0.0) && (p.getY() == 0.0) && (p.getZ() == 0.0);
    string status = get_check_status(ok);
    status += info;
    return status;
}

string check_multiply() {
    string info = "Scalar multiplication (double sided)";
    Point3 p(1.0, 1.0, 1.0);

    Point3 q = p * 2.0;
    bool ok1 = (q.getX() == 2.0) && (q.getY() == 2.0) && (q.getZ() == 2.0);

    q = 3.0 * p;
    bool ok2 = (q.getX() == 3.0) && (q.getY() == 3.0) && (q.getZ() == 3.0);

    string status = get_check_status(ok1 & ok2);
    status += info;
    return status;
}

string check_division() {
    string info = "Scalar division";
    Point3 p(1.0, 1.0, 1.0);
    Point3 q = p / 2.0;
    bool ok = (q.getX() == 0.5) && (q.getY() == 0.5) && (q.getZ() == 0.5);
    string status = get_check_status(ok);
    status += info;
    return status;
}