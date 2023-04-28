#include <iostream>
#include <chrono>
#include "Cam.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Mesh.hpp"
#include <thread>

using namespace std::chrono;

int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cout << "Usage: bin/main <path/to/output.ppm>" << std::endl;
    }
    const char* output_path = argv[1];

    std::cout << "Starting Ray Tracer..." << std::endl;

    Point3 c(5, 2, 5);
    Point3 m(1, 1, 1);
    Vec3 upVector(0, 1, 0);
    double distanceToScreen = 3;
    double scale = 1;
    int screenWidth = int(640 * scale);
    int screenHeight = int(480 * scale);

    Cam cam(c, m, upVector, distanceToScreen, screenHeight, screenWidth);

    std::cout << "Camera setup sucessfully..." << std::endl;

    std::cout << "Scene is being defined..." << std::endl;

    Scene scene(Color(0.15, 0.15, 0.15) * 0);
    
    Material wall1(Color(1, 0.5, 1));
    wall1.setKr(Color(1, 1, 1) * 0.025);
    Material wall2(Color(1, 1, .5));
    wall2.setKr(Color(1, 1, 1) * 0.025);
    Material wall3(Color(.5, 1, 1));
    wall3.setKr(Color(1, 1, 1) * 0.025);

    Material mirror_ball(Color(0.5, 0.25, 0.5));
    mirror_ball.setKs(Color(1, 1, 1));
    mirror_ball.setEta(1050);
    mirror_ball.setKr(Color(1, 1, 1) * 0.25);
    Material opaque_ball(Color(1, 0, 1), Color(1, 1, 1), Color(1, 1, 1));
    opaque_ball.setEta(100);
    Material semi_transparent(Color(1, 1, 1));
    semi_transparent.setKs(Color(1, 1, 1) * .75);
    semi_transparent.setEta(0.5);
    semi_transparent.setKr(Color(1, 1, 1) * 0);
    semi_transparent.setKt(Color(1, 1, 1));


    Sphere sp1(Point3(), 0.75, mirror_ball);
    Sphere sp2(Point3(0.25, 1, 0.25), 0.25, opaque_ball);
    Sphere sp3(Point3(1.5, 0.25, 0.25), 0.25, opaque_ball);
    Sphere sp4(Point3(0.25, 0.25, 1.5), 0.25, opaque_ball);

    Plane p1(Point3(-1, 0, -1), Vec3(1, 0, 0), wall1);
    Plane p2(Point3(0, -0.375, 0), Vec3(0, 1, 0), wall2);
    Plane p3(Point3(-1, 0, -1), Vec3(0, 0, 1), wall3);

    std::vector<Point3> vertices = {
        Point3(0, 1.25, 0),
        Point3(1.25, 0.5, 0),
        Point3(0, 0.5, 1.25)
    };

    std::vector<size_t> indices = {
        1, 0, 2
    };

    Mesh mesh(vertices, indices, wall1);

    Light ll(Point3(2.25, 0.5, 1), Color(0.95, 0.1, 0.1));
    Light lr(Point3(1, 0.5, 2.25), Color(0.1, 0.1, 0.95));
    Light lu(Point3(1, 1, 1), Color(0.95, 0.95, 0.95));

    scene.addLight(&ll);
    scene.addLight(&lr);
    scene.addLight(&lu);

    scene.addObject(&sp1);
    scene.addObject(&sp2);
    scene.addObject(&sp3);
    scene.addObject(&sp4);

    scene.addObject(&mesh);
    
    scene.addObject(&p1);
    scene.addObject(&p2);
    scene.addObject(&p3);

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