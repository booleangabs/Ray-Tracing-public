#include "Image.hpp"

#define HEIGHT 480
#define WIDTH 640

int main(int argc, char ** argv) {
    std::cout << "\n---Test Image---" << std::endl;

    std::string path = "data_output/test_image.ppm";

    Image img(HEIGHT, WIDTH);
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            img.setPixel(i, j, Color((float)i / HEIGHT, (float)j / WIDTH, 1.0));
        }
    }

    img.save(path);

    return 0;
}