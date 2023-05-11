#include <iostream>
#include <chrono>
#include "Cam.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Mesh.hpp"
#include <fstream>
#include <sstream>

#define AA_SAMPLES 7

using namespace std::chrono;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;

int main(int argc, char ** argv) {
    if (argc < 3) {
        cout << "Usage: bin/main <path/to/input.txt> <path/to/output.ppm> " << endl;
        return -1;
    }

    std::cout << "Starting Ray Tracer..." << std::endl;

    const char* input_path = argv[1];
    const char* output_path = argv[2];

    ifstream file(input_path);

    if (!file.is_open()) {
        cout << "Couldn't open file: " << input_path << endl;
        return -1;
    }

    std::cout << "Scene is being defined..." << std::endl;

    Cam cam;
    Scene scene(Color(0, 0, 0));
    Material mat = Material(Color(0, 0, 0));
    string code;
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        
        ss >> code;
        if (code == "s") {
            double cx, cy, cz, r, Or, Og, Ob, kd, ks, ka, kr, kt, p;

            ss >> cx >> cy >> cz >> r >> Or >> Og >> Ob >> kd >> ks >> ka >> kr >> kt >> p;

            mat = Material(Color(Or, Og, Ob) / 255, Color(kd, kd, kd), 
                           Color(ks, ks, ks), Color(ka, ka, ka),
                           Color(kr, kr, kr), Color(kt, kt, kt), p);
                            
            scene.addObject(new Sphere(Point3(cx, cy, cz), r, mat));
        } else if (code == "p") {
            double px, py, pz, vx, vy, vz, Or, Og, Ob, kd, ks, ka, kr, kt, p;

            ss >> px >> py >> pz >> vx >> vy >> vz >> Or >> Og >> Ob >> kd >> ks >> ka >> kr >> kt >> p;

            mat = Material(Color(Or, Og, Ob) / 255, Color(kd, kd, kd), 
                           Color(ks, ks, ks), Color(ka, ka, ka),
                           Color(kr, kr, kr), Color(kt, kt, kt), p);
            scene.addObject(new Plane(Point3(px, py, pz), Vec3(vx, vy, vz), mat));
        } else if (code == "t") {
            std::vector<Point3> vertices;
            std::vector<size_t> idx;
            int n_t, n_v, ti0, ti1, ti2;
            ss >> n_t >> n_v;

            double px, py, pz;
            for (int i = 0; i < n_v; i++) {
                getline(file, line);
                ss = istringstream(line);
                ss >> px >> py >> pz;
                vertices.push_back(Point3(px, py, pz));
            }

            for (int i = 0; i < n_t; i++) {
                getline(file, line);
                ss = istringstream(line);
                ss >> ti0 >> ti1 >> ti2;
                idx.push_back(ti0);
                idx.push_back(ti1);
                idx.push_back(ti2);
            }

            getline(file, line);
            ss = istringstream(line);
            double Or, Og, Ob, kd, ks, ka, kr, kt, p;
            ss >> Or >> Og >> Ob >> kd >> ks >> ka >> kr >> kt >> p;

            mat = Material(Color(Or, Og, Ob) / 255, Color(kd, kd, kd), 
                           Color(ks, ks, ks), Color(ka, ka, ka),
                           Color(kr, kr, kr), Color(kt, kt, kt), p);
            scene.addObject(new Mesh(vertices, idx, mat));
        } else if (code == "c") {
            int hres, vres;
            double d, upx, upy, upz, Cx, Cy, Cz, Mx, My, Mz;

            ss >> hres >> vres >> d >> upx >> upy >> upz >> Cx >> Cy >> Cz >> Mx >> My >> Mz;

            cam = Cam(Point3(Cx, Cy, Cz), Point3(Mx, My, Mz), Vec3(upx, upy, upz),
                      d, vres, hres);
        } else if (code == "l") {
            double lx, ly, lz, ilx, ily, ilz;
            
            ss >> lx >> ly >> lz >> ilx >> ily >> ilz;
            
            scene.addLight(new Light(Point3(lx, ly, lz), Color(ilx, ily, ilz) / 255));
        } else if (code == "a") {
            double Iax, Iay, Iaz;

            ss >> Iax >> Iay >> Iaz;

            scene.setAmbientColor(Color(Iax, Iay, Iaz) / 255);
        }

    }

    cout << "Rendering " << cam.getScreenWidth() << "x" << cam.getScreenHeight() << " result..." << endl;
    
    Image result(cam.getScreenWidth(), cam.getScreenHeight());
    auto t0 = high_resolution_clock::now();

    result = cam.render(scene, AA_SAMPLES);
    
    auto t1 = high_resolution_clock::now();
    double time = duration_cast<milliseconds>(t1 - t0).count();
    std::cerr << "Took " << time << "ms to render!" << std::endl;

    result.save(output_path);

    return 0;
}