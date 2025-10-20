#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "src/loadwritevideo.hpp"
#include "src/functions/dummy.hpp"

// help message
void printHelp() {
    std::cout << "Usage: ./main <path-to-video-file> [flag]\n\n"
              << "Available flags:\n"
              << "  -h, --help      Show this help message\n"
              << "  -d, --dummy     Use the dummy function (default)\n";
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

        //ADD NEW ABOVE HERE (func = whatever i want)
        else {
            std::cerr << "Unknown flag: " << flag << "\n";
            printHelp();
            return -1;
        }
    } else {
        std::cout << "No flag provided, running dummy by default.\n";
    }

    if (!saveVideo(cap, func)) {
        std::cout << "Failed to save video" << std::endl;
    }

    cv::destroyAllWindows();
    return 0;
}
