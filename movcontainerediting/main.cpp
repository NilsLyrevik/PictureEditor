#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include "src/loadwritevideo.hpp"
#include "src/functions/dummy.hpp"
#include "src/functions/grayscale.hpp"
#include "src/functions/gaussianblur.hpp"
#include "src/functions/sobel.hpp"
#include "src/functions/drawedges.hpp"
#include "src/removebackground/removebackground.hpp"  // <-- add this

// help message
void printHelp() {
    std::cout << "Usage: ./main <path-to-video-file> [flag]\n\n"
              << "Available flags:\n"
              << "  -h, --help        Show this help message\n"
              << "  -d, --dummy       Use the dummy function (default)\n"
              << "  -g, --gray        Use the grayscale function\n"
              << "  -b, --blur        Use the gaussian blur function\n"
              << "  -s, --sobel       Use the sobel edge detection function\n"
              << "  -e, --edge        Use the sobel edge detection function and plot edges\n"
              << "  -r, --removebg    Run background removal (MOG2 by default, KNN if 'knn' flag provided)\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
        return -1;
    }

    std::string filename = argv[1];
    cv::VideoCapture cap = loadVideo(filename);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video.\n";
        return -1;
    }

    // default function pointer (dummy)
    cv::Mat (*func)(cv::Mat) = dummy;
    bool useRemoveBackground = false;
    bool useMOG2 = true; // default for RemoveBackground

    // handle flags
    if (argc >= 3) {
        std::string flag = argv[2];
        if (flag == "-h" || flag == "--help") {
            printHelp();
            return 0;
        } 
        else if (flag == "-d" || flag == "--dummy") {
            func = dummy;
        } 
        else if (flag == "-g" || flag == "--gray") {
            func = grayscale;
        }
        else if (flag == "-b" || flag == "--blur") {
            func = gaussianblur;
        }
        else if (flag == "-s" || flag == "--sobel") {
            func = sobel;
        }
        else if (flag == "-e" || flag == "--edge") {
            func = drawedges;
        }
        else if (flag == "-r" || flag == "--removebg") {
            useRemoveBackground = true;
            if (argc >= 4 && std::string(argv[3]) == "knn") {
                useMOG2 = false; // optional third arg for method choice
            }
        }
        else {
            std::cerr << "Unknown flag: " << flag << "\n";
            printHelp();
            return -1;
        }
    } else {
        std::cout << "No flag provided, running dummy by default.\n";
    }

    auto start = std::chrono::high_resolution_clock::now();

    bool success = false;
    if (useRemoveBackground) {
        success = RemoveBackground(cap, useMOG2);
    } else {
        success = saveVideo(cap, func);
    }

    if (!success) {
        std::cout << "Failed to process video" << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " s\n";

    cv::destroyAllWindows();
    return 0;
}
