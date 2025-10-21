OpenCV Video Processor
======================

A simple C++ program for applying basic image processing filters (like grayscale, blur, and edge detection) to an entire video using OpenCV.

This project loads a video, applies a selected transformation frame by frame, and writes the processed video to an output file.

------------------------------------------------------------

Features
--------

- Load and process .mp4, .mov, or other supported video formats
- Apply one of several built-in filters to every frame:
  - Dummy – no processing (default)
  - Grayscale – converts frames to grayscale
  - Gaussian Blur – applies a soft blur to smooth noise
  - Sobel Edge Detection – highlights edges in the video

------------------------------------------------------------

Requirements
------------

- C++17 or later
- CMake 3.10+
- OpenCV 4.x

Make sure OpenCV is installed and visible to CMake.
On macOS, for example:
    brew install opencv

------------------------------------------------------------

Build Instructions
------------------

    git clone <your-repo-url>
    cd movcontainerediting
    mkdir build && cd build
    cmake ..
    make

This will produce an executable called "main" in your build/ directory.

------------------------------------------------------------

Usage
-----

Run the program from the build/ directory:

    ./main <path-to-video> [flag]

Example:

    ./main ../testmovs/IMG_8521.MOV -g

This loads IMG_8521.MOV, applies grayscale, and writes the processed output to:

    ../output/output.mp4

------------------------------------------------------------

Available Flags
---------------

    -h, --help      Show help message
    -d, --dummy     Use dummy (no change) — default
    -g, --gray      Convert video to grayscale
    -b, --blur      Apply Gaussian blur
    -s, --sobel     Apply Sobel edge detection
    -e, --edge      Apply Sobel with thresholding over original video

If no flag is provided, the dummy function runs by default.

------------------------------------------------------------

Project Structure
-----------------
```
    movcontainerediting/
    ├── main.cpp
    ├── CMakeLists.txt
    ├── src/
    │   ├── loadwritevideo.cpp
    │   ├── loadwritevideo.hpp
    │   └── functions/
    │       ├── dummy.cpp / .hpp
    │       ├── drawedges.cpp / .hpp
    │       ├── grayscale.cpp / .hpp
    │       ├── gaussianblur.cpp / .hpp
    │       └── sobel.cpp / .hpp
    ├── output/ # created when running
    │   └── (processed videos saved here)
    └── testmovs/
        └── (input videos for testing)
```

------------------------------------------------------------

Extending the Program
---------------------

To add a new filter:
1. Create a new .cpp and .hpp in src/functions/
2. Implement a function with this signature:
       cv::Mat myfilter(cv::Mat frame);
3. Include it in main.cpp:
       #include "src/functions/myfilter.hpp"
4. Add a flag in main:
       else if (flag == "-m" || flag == "--myfilter") {
           func = myfilter;
       }
5. Rebuild with make.

------------------------------------------------------------

Cleaning Up
-----------

To rebuild from scratch:

    make clean
    rm -rf build/*
    mkdir build && cd build
    cmake ..
    make

Note: Output files in output/ are not deleted by "make clean" — remove them manually if needed.