#include "Point3.hpp"
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream &s, const rtc::Point3 &p) {
    return s << "Point3(" << p.x << ", " << p.y << ", " << p.z << ")";
}

istream& operator>>(istream &s, rtc::Point3 &p) {
    return s >> p.x >> p.y >> p.z;
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

string check_empty_init(const rtc::Point3 &p);

int main(int argc, char ** argv) {
    bool ok;
    string status;
    string details;
    vector<string> prints;

    rtc::Point3 p;
    
    prints.push_back(check_empty_init(p));
    
    // cout << "Provide 3 coordinates for a point: \n";
    // cin >> p;
    // cout << p;

    for (auto s : prints)
        cout << s << endl;
}

string check_empty_init(const rtc::Point3 &p) {
    string info = "Empty point should initialize to origin";
    bool ok = (p.x == 0.0) && (p.y == 0.0) && (p.z == 0.0);
    string status = get_check_status(ok);
    status += info;
    return status;
}