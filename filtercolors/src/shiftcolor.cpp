#include <iostream>
#include <iterator>
#include "shiftcolor.h"

void shiftcolor(unsigned char* data, int width, int height, int channels){
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) { 
            int idx = (j * width + i) * channels;
            unsigned char temp = data[idx];
            //if (channels == 3){
                data[idx] = data[idx + 1]; 
                data[idx + 1] = data[idx + 2];
                data[idx + 2] = temp; 
            //}
            /*
            else { //if channels == 4 (i think png can only be 3 or 4 channels)
            data[idx] = data[idx + 1]; 
            data[idx + 1] = data[idx + 2];
            data[idx + 2] = data[idx + 3]
        }
        */
        }
    }
}