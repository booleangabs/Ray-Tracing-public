#ifndef IMAGE_H
#define IMAGE_H

#include "Color.hpp"
#include <vector>
#include <iostream>
#include <fstream>

class Image {
    private:
        std::vector<Color> data;
        int height, width;

    public:
        Image(int _height, int _width);
        
        Color getPixel(int i, int j) const;
        void setPixel(int i, int j, Color c);

        void save(std::string path);
};

#endif