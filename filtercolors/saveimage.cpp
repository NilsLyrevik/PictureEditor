#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "../stb_image/stb_image_write.h"

#include "saveimage.h"
#include <iostream>

bool saveimage(const char* filename, unsigned char* data, int width, int height, int channels) {
    if (stbi_write_png(filename, width, height, channels, data, width * channels)) {
        std::cout << "Saved copy to " << filename << std::endl;
        return true;
    } else {
        std::cerr << "Failed to save image to " << filename << std::endl;
        return false;
    }
}