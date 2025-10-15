/*
The idea is to convert the image in diffrent steps:

    1. color -> grayscale

    2. gaussian blur (small one)

    3. Sobel algorithm!


(SOURCE: Computerphile: Finding the Edges (Sobel Operator) )
*/
#include "loadimage.h"
#include "saveimage.h"
#include "grayscale.h"
#include "gaussianblur.h"
#include "sobel.h"
#include <iostream>
#include <cstring> // for strcmp

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image> <output_image> [--color]" << std::endl;
        return 1;
    }

    // Parse optional flag
    bool colorflag = false;
    if (argc >= 4 && std::strcmp(argv[3], "--color") == 0) {
        colorflag = true;
        std::cout << "Color mode enabled!" << std::endl;
    }

    // Load image
    int width, height, channels;
    unsigned char* data = loadimage(argv[1], width, height, channels);
    if (!data) return 1;

    // Pipeline
    grayscale(data, width, height, channels);     // Step 1: Convert to grayscale
    gaussianblur(data, width, height, channels);  // Step 2: Blur to reduce noise
    sobelfilter(data, width, height, channels, colorflag); // Step 3: Sobel edge detection

    // Save result
    if (!saveimage(argv[2], data, width, height, channels)) {
        std::cerr << "Could not save image!" << std::endl;
    } else {
        std::cout << "Saved result successfully!" << std::endl;
    }

    freeimage(data);
    return 0;
}
