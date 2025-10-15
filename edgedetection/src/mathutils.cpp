#include "mathutils.h"

int clamp_int(int input, int low, int high) {
    if (input > high) return high;
    if (input < low) return low;
    return input;
}

float clamp_float(float input, float low, float high) {
    if (input > high) return high;
    if (input < low) return low;
    return input;
}
