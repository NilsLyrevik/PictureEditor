#include "loadimage.h"
#include "saveimage.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image> <output_image>" << std::endl;
        return 1;
    }

    int width, height, channels;
    unsigned char* data = loadimage(argv[1], width, height, channels);
    if (!data) return 1;

    if (!saveimage(argv[2], data, width, height, channels)) {
        std::cerr << "Could not save image!" << std::endl;
    } else {
        std::cout << "Success!" << std::endl;
    }

    freeimage(data);
    return 0;
}

