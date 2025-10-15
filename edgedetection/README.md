# Edge Detection Pipeline

This project performs basic edge detection using a simple image-processing pipeline written in C++.

## Folder Structure
´´´
 ├──edgedetection/
 │  ├── result/              # Output images are saved here
 │  ├── src/                 # Source code files
 │      ├── main.cpp
 │      ├── loadimage.cpp / .h
 │      ├── saveimage.cpp / .h
 │      ├── grayscale.cpp / .h
 │      ├── gaussianblur.cpp
 │      └── sobel.cpp        # (to be implemented )
 └──stb_image/        # External STB image libraries
´´´
## Pipeline Overview

1. Load Image – Reads an image using stb_image.
2. Grayscale Conversion – Converts RGB images to grayscale using the luminosity method.
3. Gaussian Blur – Applies a 3x3 Gaussian filter to reduce noise.
4. Sobel Operator (upcoming) – Detects edges by computing image gradients.

## Build Instructions

From the edgedetection directory:

make

## Run Instructions

To process an image:

make run INPUT=../testpictures/volcano.png

The output will be written to:

edgedetection/result/output.png

## Clean

To remove compiled objects and generated result images:

make clean

## Dependencies

- C++17 compiler
- stb_image.h
- stb_image_write.h
