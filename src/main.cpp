#include <iostream>
#include <chrono>
#include "Cam.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include <thread>

using namespace std::chrono;

int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cout << "Usage: bin/main <path/to/output.ppm>" << std::endl;
    }
    const char* output_path = argv[1];

    std::cout << "Starting Ray Tracer..." << std::endl;

    Point3 c(5, 5, 5);
    Point3 m(1, 1, 1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 3;
    double scale = 3;
    int screenWidth = int(640 * scale);
    int screenHeight = int(480 * scale);

    Cam cam(c, m, upVector, distanceToScreen, screenHeight, screenWidth);

    std::cout << "Camera setup sucessfully..." << std::endl;

    std::cout << "Scene is being defined..." << std::endl;

    Scene scene(Color(0.25, 0.25, 0.25));
    
    Material wall1(Color(0.95, 0.5, 0.5));
    Material wall2(Color(0.5, 0.95, 0.5));
    Material wall3(Color(0.5, 0.5, 0.95));
    Material highlighted_ball(Color(1, 1, 1));
    highlighted_ball.setKs(Color(1, 1, 1) * 0.75);
    highlighted_ball.setEta(50);

    Sphere sp1(Point3(), 1.0, Material(Color(0.75, 0.75, 0.75)));
    Sphere sp2(Point3(0.45, 1.5, 0.45), 0.25, highlighted_ball);
    Sphere sp3(Point3(1.5, 0.45, 0.45), 0.25, highlighted_ball);
    Sphere sp4(Point3(0.45, 0.45, 1.5), 0.25, highlighted_ball);

    Plane p1(Point3(), Vec3(1, 0, 0), wall1);
    Plane p2(Point3(), Vec3(0, 1, 0), wall2);
    Plane p3(Point3(), Vec3(0, 0, 1), wall3);
    Plane p4(Point3(0.5, 0.5, 0.5), Vec3(-1, -1, -1), wall2);

    Light l1(Point3(3, 1, 1), Color(1, 0, 0));
    Light l2(Point3(1, 1, 3), Color(0, 1, 0));
    Light l3(Point3(1, 3, 1), Color(0, 0, 1));

    scene.addObject(&sp1);
    scene.addObject(&sp2);
    scene.addObject(&sp3);
    scene.addObject(&sp4);
    
    scene.addObject(&p1);
    scene.addObject(&p2);
    scene.addObject(&p3);
    scene.addObject(&p4);

    scene.addLight(&l1);
    scene.addLight(&l2);
    scene.addLight(&l3);

    std::cout << "Rendering " << screenWidth << "x" << screenHeight << " result..." << std::endl;
    
    Image result(screenHeight, screenWidth);
    auto t0 = high_resolution_clock::now();

    result = cam.render(scene);
    
    auto t1 = high_resolution_clock::now();
    double time = duration_cast<milliseconds>(t1 - t0).count();
    std::cerr << "Took " << time << "ms to render!" << std::endl;

    result.save(output_path);

    return 0;
}