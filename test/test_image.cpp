#include "Image.hpp"

#define HEIGHT 480
#define WIDTH 640

int main(int argc, char ** argv) {
    std::cout << "\n---Test Image---" << std::endl;
    if (argc < 2) {
        std::cout << "Output path missing. Usage: ./test_image.(o/exe) <output/file/path>" << std::endl;
        return -1;
    }
    const std::string path = (std::string) argv[1];

    Image img(HEIGHT, WIDTH);
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            img.setPixel(i, j, Color((float)i / HEIGHT, (float)j / WIDTH, 0.0));
        }
    }

    img.save(path);

    return 0;
}