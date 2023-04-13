#include "Image.hpp"

Image::Image(int _height, int _width) {
    data = std::vector<Color>(_height * _width, Color());
    height = _height;
    width = _width;
}

Color Image::getPixel(int i, int j) const {
    return data[i * width + j];
}

void Image::setPixel(int i, int j, Color c) {
    data[i * width + j] = c;
}

void Image::save(std::string path) {
    std::ofstream file;
    file.open(path);

    if (!file.is_open()) {
        std::cout << "Unable to open '" << path << "'" << std::endl;
        return;
    }
    
    file << "P3" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;

    std::cerr << "Writing image -> ";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Color current = getPixel(i, j);
            int r = static_cast<uint8_t>(255.99 * current.r);
            int g = static_cast<uint8_t>(255.99 * current.g);
            int b = static_cast<uint8_t>(255.99 * current.b);
            file << r << " " << g << " " << b << std::endl;
        }
    }

    std::cerr << "Image saved to '" << path << "'!" << std::endl;
    file.close();
}