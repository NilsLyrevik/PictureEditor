#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"
#include <iostream>

unsigned char* loadimage(const char* filename) {
    int width, height, channels;

    unsigned char* data = stbi_load(filename , &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load image!" << std::endl;
        return 0;
    }

    std::cout << "Loaded image with size " 
              << width << "x" << height 
              << " and " << channels << " channels." << std::endl;
    
    stbi_load("output.png", &width, &height, &channels, 0);

    // Free memory when done
    stbi_image_free(data);

    return 0;
}
