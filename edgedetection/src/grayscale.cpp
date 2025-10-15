#include <iostream>
#include <iterator>
#include "grayscale.h"

// based on luminosity method
unsigned char naturalgray(unsigned char red, unsigned char green, unsigned char blue){
    return static_cast<unsigned char>((red * 0.299f) + (green * 0.587f) + (blue * 0.114f));
}

unsigned char simplegray(unsigned char red, unsigned char green, unsigned char blue){
    return ((int)red + (int)green + (int)blue)/3;
}

void grayscale(unsigned char* data, int width, int height, int channels){
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) { 
            
            int idx = (j * width + i) * channels;

            unsigned char gray = naturalgray(data[idx],data[idx + 1],data[idx + 2]);
            //                 = simplegray(data[idx],data[idx + 1],data[idx + 2]);
                data[idx] = gray;
                data[idx + 1] = gray;
                data[idx + 2] = gray;
        }
    }
}