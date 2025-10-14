#define STB_IMAGE_IMPLEMENTATION 
#include "../stb_image/stb_image.h"
#include "loadimage.h"
#include <iostream>

void freeimage(unsigned char* data) {
    stbi_image_free(data);
}

unsigned char* loadimage(const char* filename, int& width, int& height, int& channels) {
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image!" << std::endl;
        return nullptr;
    }
    std::cout << "Loaded image with size " << width << "x" << height
              << " and " << channels << " channels." << std::endl;
    return data;
}
