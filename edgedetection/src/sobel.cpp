/*
The idea is to convert the image in diffrent steps:

    1. color -> grayscale

    2. gaussian blur (small one)

    3. Sobel algorithm!


(SOURCE: Computerphile: Finding the Edges (Sobel Operator) )
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "gaussianblur.h"
#include "mathutils.h"

void sobelfilter(unsigned char* data, int width, int height, int channels){

    //this is what will be applied to every pixel (around every pixel)
    float xkernel[3][3] = {
        {-1.f,0.f,1.f},
        {-2.f,0.f,2.f},
        {-1.f,0.f,1.f}
    };

        float ykernel[3][3] = {
        {-1.f,-2.f,-1.f},
        {0.f,0.f,0.f},
        {1.f,2.f,1.f}
    };

    // Copy since we will be overwriting data. 
    std::vector<unsigned char> original(data, data + width * height * channels); // NO NEED FOR FREEING MEMORY (c++ takes care of this :D )

    int kernelRadius = 1; 

    for (int x = 0; x < width; ++x) { //++x instead of x++ is "faster" (ever so slightly)
        for (int y = 0; y < height; ++y) {

            float gx = 0.0f;
            float gy = 0.0f;

            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky){ 
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx){

                    int ny = clamp_int(y + ky, 0, height - 1);
                    int nx = clamp_int(x + kx, 0, width - 1);
                    int nidx = (ny * width + nx) * channels;

                    gx += xkernel[ky + 1][kx + 1] * original[nidx];
                    gx += xkernel[ky + 1][kx + 1] * original[nidx];
                }
            }
            float magnitude = std::abs(gx) + std::abs(gy); // should be sqrt(gx*gx + gy*gy) but this is more nicer to the computer
            int idx = (y* width + x) * channels;
            data[idx] = static_cast<unsigned char>(clamp_float(magnitude, 0.0f, 255.0f));
            data[idx + 1] = static_cast<unsigned char>(clamp_float(magnitude, 0.0f, 255.0f));
            data[idx + 2] = static_cast<unsigned char>(clamp_float(magnitude, 0.0f, 255.0f));
        }
    }
}
