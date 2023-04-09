#include "Scene.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <memory>

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
string check_init();
string check_dummy_object_intersect();

class DummyObject : public Object {
    public:
        bool does_hit;

        DummyObject(bool _dh) : does_hit(_dh) {};

        virtual bool intersect(const Ray& ray, double t_min, HitRecord& hitRecord) const {
            // Intersection distance is random between 0 and 1
            hitRecord.distance = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
            return does_hit;
        }
};

int main(int argc, char ** argv) {
    std::cout << "\n---Test Scene---" << std::endl;

    bool ok;
    string status;
    string details;
    vector<string> prints;
    
    prints.push_back(check_empty_init());
    prints.push_back(check_init());
    prints.push_back(check_dummy_object_intersect());

    for (auto s : prints)
        cout << s << endl;
}

string check_empty_init() {
    string info = "Empty initialization";
    Scene scene = Scene();
    bool ok1 = (scene.getAmbientColor().r == 0) 
                && (scene.getAmbientColor().g == 0) 
                && (scene.getAmbientColor().b == 0);
    bool ok2 = scene.getNumObjects() == 0;
    string status = get_check_status(ok1 && ok2);
    status += info;
    return status;
}

string check_init() {
    string info = "Regular initialization and Object storage";
    Scene scene(Color(0.5, 0.5, 1.0));
    HitRecord r = HitRecord();
    double d1, d2;

    for (int i = 0; i <= 1; i++)
        scene.addObject(new DummyObject((bool) i));

    bool ok1 = (scene.getAmbientColor().r == 0.5) 
                && (scene.getAmbientColor().g == 0.5) 
                && (scene.getAmbientColor().b == 1.0);
    bool ok2 = scene.getNumObjects() == 2;
    bool ok3 = !scene[0]->intersect(Ray(), 0, r);
    d1 = r.distance;
    bool ok4 = scene[1]->intersect(Ray(), 0, r);
    d2 = r.distance;
    bool ok5 = d1 != d2;
    
    string status = get_check_status(ok1 && ok2 && ok3 && ok4 && ok5);
    status += info;
    return status;
}

string check_dummy_object_intersect() {
    string info = "Dummy object intersection";
    Scene scene(Color(0.5, 0.5, 1.0));
    HitRecord r = HitRecord();
    double d1, d2;

    for (int i = 0; i <= 5; i++)
        scene.addObject(new DummyObject(false));

    bool ok1 = !scene.intersect(Ray(), r);
    scene.addObject(new DummyObject(true));
    bool ok2 = scene.intersect(Ray(), r);
    bool ok3 = r.distance > 0;

    string status = get_check_status(ok1 && ok2 && ok3);
    status += info;
    return status;
}