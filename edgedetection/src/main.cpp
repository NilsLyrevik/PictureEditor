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
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image> <output_image>" << std::endl;
        return 1;
    }

    //LOAD IMAGE
    int width, height, channels;
    unsigned char* data = loadimage(argv[1], width, height, channels);
    if (!data) return 1;

    //METHODS/ FUNCTIONS FOR EDITING HERE!!!!
    grayscale(data, width, height, channels);
    gaussianblur(data, width, height, channels);

    // SAVE IMAGE
    if (!saveimage(argv[2], data, width, height, channels)) {
        std::cerr << "Could not save image!" << std::endl;
    } else {
        std::cout << "Success!" << std::endl;
    }

    freeimage(data);
    return 0;
}

