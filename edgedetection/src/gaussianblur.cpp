#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "gaussianblur.h"
#include "mathutils.h"

void gaussianblur(unsigned char* data, int width, int height, int channels){

    //this is what will be applied to every pixel (around every pixel)
    float kernel[3][3] = {
        {1.f/16,2.f/16,1.f/16},
        {2.f/16,4.f/16,2.f/16},
        {1.f/16,2.f/16,1.f/16}
    };

    // Copy since we will be overwriting data. 
    std::vector<unsigned char> original(data, data + width * height * channels); // NO NEED FOR FREEING MEMORY (c++ takes care of this :D )

    int kernelRadius = 1; //need to make more variables like these. good for future editing of code!

    for (int x = 0; x < width; ++x) { //++x instead of x++ is "faster" (ever so slightly)
        for (int y = 0; y < height; ++y) {

            float sum = 0.0f;

            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky){ 
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx){

                    int ny = clamp_int(y + ky, 0, height - 1);
                    int nx = clamp_int(x + kx, 0, width - 1);
                    int nidx = (ny * width + nx) * channels;

                    sum += kernel[ky + 1][kx + 1] * original[nidx];

                }
            }

            int idx = (y* width + x) * channels;
            data[idx] = static_cast<unsigned char>(clamp_float(sum, 0.0f, 255.0f));
            data[idx + 1] = static_cast<unsigned char>(clamp_float(sum, 0.0f, 255.0f));
            data[idx + 2] = static_cast<unsigned char>(clamp_float(sum, 0.0f, 255.0f));
        }
    }
}